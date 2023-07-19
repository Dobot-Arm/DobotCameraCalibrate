#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Logger.h"
#include "MessageCenter/MessageCenter.h"

#include <QDesktopServices>
#include <QMessageBox>
#include <QThread>
#include <QtConcurrent>
#include <QProcess>
#include <QTextCodec>

MainWindow::MainWindow(QHash<QString,QString> args, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_argsOptions(args)
{
    ui->setupUi(this);

    enableAdvFirewall();

    //日志信号槽
    connect(CLogger::getInstance(), &CLogger::signalPrintLogMsg,
            this, &MainWindow::slotAppendLog);

    //start server
    CMessageCenter::getInstance()->start();
    connect(CMessageCenter::getInstance(), &CMessageCenter::signalShowWindow, this, &MainWindow::show);
    connect(CMessageCenter::getInstance(), &CMessageCenter::signalHideWindow, this, &MainWindow::hide);
    connect(CMessageCenter::getInstance(), &CMessageCenter::signalExitWindow, this, &MainWindow::slotExitApp);
    connect(CMessageCenter::getInstance(), &CMessageCenter::signalLoggerOn, ui->checkBoxLogFile, &QCheckBox::toggled);

    ui->checkBoxLogFile->setChecked(CLogger::getInstance()->isLogOnFile());
    ui->checkBoxLogWnd->setChecked(CLogger::getInstance()->isLogEmitted());
    connect(ui->checkBoxLogFile, &QCheckBox::toggled, this, &MainWindow::slotLogOnFile);
    connect(ui->checkBoxLogWnd, &QCheckBox::toggled, this, &MainWindow::slotLogOnWnd);
    connect(ui->btnClearLog, &QPushButton::clicked, this, &MainWindow::slotClearLog);

    connect(ui->actionTest, &QAction::triggered, this, &MainWindow::slotActionTest);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* pEvent)
{
    auto result = QMessageBox::question(nullptr, tr("tips"), tr("Are you sure quit app?"),
                                        QMessageBox::Yes|QMessageBox::No, QMessageBox::No);
    if (result == QMessageBox::Yes)
    {
        pEvent->accept();
        slotExitApp();
    }
    else
    {
        pEvent->ignore();
    }
}

void MainWindow::enableAdvFirewall()
{
    QtConcurrent::run([]{
        QProcess *p = new QProcess();
        p->setProcessChannelMode(QProcess::MergedChannels);
        connect(p, &QProcess::readyRead, [p]{
            QTextCodec *codec = QTextCodec::codecForName("GBK");
            qDebug()<<"QProcess::readyRead-->"<<codec->toUnicode(p->readAll());
        });
        connect(p, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),[](int code, QProcess::ExitStatus sta){
            qDebug()<<"QProcess::finished-->"<<code<<","<<sta;
        });
        connect(p, &QProcess::errorOccurred, [](QProcess::ProcessError error){
            qDebug()<<"QProcess::errorOccurred-->"<<error;
        });

        //先删除，防止太多重复的
        p->start("netsh advfirewall firewall delete rule name=\"dobotcalibrate\"");
        p->waitForFinished(1000);
        p->start("netsh advfirewall firewall delete rule name=\"DobotCalibrate\"");
        p->waitForFinished(1000);

        QThread::sleep(2);
        //再添加，防止前端没有主动调用OpenFireWall开启
        QString strUdpAdd = QString("netsh advfirewall firewall add rule name=\"dobotcalibrate\" dir=in "
                            "action=allow program=\"%1\" enable=yes profile=any "
                            "protocol=UDP localport=").arg(QDir::toNativeSeparators(qApp->applicationFilePath()));
        QString strTcpAdd = QString("netsh advfirewall firewall add rule name=\"dobotcalibrate\" dir=in "
                            "action=allow program=\"%1\" enable=yes profile=any "
                            "protocol=TCP localport=").arg(QDir::toNativeSeparators(qApp->applicationFilePath()));

        p->start(strUdpAdd);
        p->waitForFinished(2000);
        p->start(strTcpAdd);
        p->waitForFinished(2000);
        p->deleteLater();
    });
}

void MainWindow::slotLogOnFile(bool bOn)
{
    CLogger::getInstance()->setLogOnFile(bOn);
}

void MainWindow::slotLogOnWnd(bool bOn)
{
    CLogger::getInstance()->setLogEmitted(bOn);
}

void MainWindow::slotAppendLog(const QString& strLog)
{
    ++m_iLogCount;
    if (m_iLogCount>100)
    {
        slotClearLog();
        m_iLogCount = 0;
    }
    if (strLog.length()>1024)
    {
        ui->textBrowserLog->append("text is too large, does not print");
    }
    else
    {
        ui->textBrowserLog->append(strLog);
    }
}

void MainWindow::slotClearLog()
{
    ui->textBrowserLog->clear();
    m_iLogCount = 0;
}

void MainWindow::slotExitApp()
{
    CMessageCenter::getInstance()->stop();
    CMessageCenter::destroyInstance();
    qApp->quit();
}

void MainWindow::slotActionTest()
{
    QString strFile = qApp->applicationDirPath()+QDir::separator()+"websocket-camera.html";
    qDebug()<<QDesktopServices::openUrl(QUrl::fromLocalFile(strFile));
}
