#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Logger.h"
#include "MessageCenter/MessageCenter.h"
#include "DefineMicro.h"
#include "DError.h"
#include "DataBean/SearchCameraBean.h"
#include "DataBean/OpenCameraBean.h"
#include "DataBean/CloseCameraBean.h"
#include "DataBean/StartVideoImageBean.h"
#include "DataBean/StopVideoBean.h"

#include <QMessageBox>
#include <QThread>
#include <QtConcurrent>
#include <QProcess>
#include <QTextCodec>
#include <QMessageBox>
#include <QFileDialog>

#define LogConsole() (*this)

static bool isSameNetworkSegment(const QString &ip1, const QString &ip2, const QString &netmask="255.255.255.0")
{
    QHostAddress addr1(ip1);
    QHostAddress addr2(ip2);
    QHostAddress mask(netmask);

    if(addr1.isNull() || addr2.isNull() || mask.isNull())
    {
        return false;
    }

    quint32 ip1Int = addr1.toIPv4Address();
    quint32 ip2Int = addr2.toIPv4Address();
    quint32 maskInt = mask.toIPv4Address();

    quint32 network1 = ip1Int & maskInt;
    quint32 network2 = ip2Int & maskInt;

    return network1 == network2;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    enableAdvFirewall();

    //start server
    CMessageCenter::getInstance()->start();

#ifdef QT_DEBUG
    //日志信号槽
    connect(CLogger::getInstance(), &CLogger::signalPrintLogMsg, this, &MainWindow::slotAppendLog);
    CLogger::getInstance()->setLogEmitted(true);
    connect(CMessageCenter::getInstance(), &CMessageCenter::signalExitWindow, this, &MainWindow::slotExitApp);
#endif

    m_pWSClient = new QWebSocket("", QWebSocketProtocol::VersionLatest, this);
    m_pWSClient->setProxy(QNetworkProxy::NoProxy);
    connect(m_pWSClient, &QWebSocket::connected, this, &MainWindow::slotConnected);
    connect(m_pWSClient, &QWebSocket::disconnected, this, &MainWindow::slotDisconnected);
    connect(m_pWSClient, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &MainWindow::slotError);
    connect(m_pWSClient, &QWebSocket::textMessageReceived, this, &MainWindow::slotTextRecv);

    m_pTimerReconnect = new QTimer(this);
    m_pTimerReconnect->setInterval(1000);
    m_pTimerReconnect->setSingleShot(true);
    connect(m_pTimerReconnect, &QTimer::timeout, this, &MainWindow::slotReconnected);

    m_pSearch = new QTimer(this);
    m_pSearch->setInterval(1000);
    m_pSearch->setSingleShot(true);
    connect(m_pSearch, &QTimer::timeout, this, &MainWindow::slotSearchCamera);

    slotReconnected();

    ui->lineEditPath->setReadOnly(true);
    connect(ui->btnStart, &QPushButton::clicked, this, &MainWindow::slotOnStart);
    connect(ui->btnStop, &QPushButton::clicked, this, &MainWindow::slotOnStop);
    connect(ui->btnSelect, &QPushButton::clicked, this, &MainWindow::slotOnSelect);
    ui->btnSelect->setEnabled(true);
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);

    QString strInfo = "1. 打开此工具前，请先关闭相机插件，否则此工具无法正常工作。\r\n"
"   Before opening this tool, please close the camera plug-in first, otherwise this tool will not work properly.\r\n\r\n"
"2. 如果需要打开相机插件，请先关闭此工具，否则相机插件无法正常工作。\r\n"
"   If you need to open the camera plug-in, please close this tool first, otherwise the camera plug-in will not work properly.";
    ui->labelInfo->setText(strInfo);
    QDir dirDefault(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation));
    const QString strDefaultPath = QDir::toNativeSeparators(dirDefault.absoluteFilePath("VX500"));
    ui->lineEditPath->setText(strDefaultPath);
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
        slotOnStop();
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
        p->start("netsh advfirewall firewall delete rule name=\"dobotcameraimage\"");
        p->waitForFinished(1000);
        p->start("netsh advfirewall firewall delete rule name=\"DobotCameraImage\"");
        p->waitForFinished(1000);

        QThread::sleep(2);
        //再添加，防止前端没有主动调用OpenFireWall开启
        QString strUdpAdd = QString("netsh advfirewall firewall add rule name=\"dobotcameraimage\" dir=in "
                            "action=allow program=\"%1\" enable=yes profile=any "
                            "protocol=UDP localport=").arg(QDir::toNativeSeparators(qApp->applicationFilePath()));
        QString strTcpAdd = QString("netsh advfirewall firewall add rule name=\"dobotcameraimage\" dir=in "
                            "action=allow program=\"%1\" enable=yes profile=any "
                            "protocol=TCP localport=").arg(QDir::toNativeSeparators(qApp->applicationFilePath()));

        p->start(strUdpAdd);
        p->waitForFinished(2000);
        p->start(strTcpAdd);
        p->waitForFinished(2000);
        p->deleteLater();
    });
}

void MainWindow::slotAppendLog(const QString& strLog)
{
    ++m_iLogCount;
    if (m_iLogCount>200)
    {
        ui->textBrowserLog->clear();
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

void MainWindow::slotExitApp()
{
    CMessageCenter::getInstance()->stop();
    CMessageCenter::destroyInstance();
    qApp->quit();
}

void MainWindow::startResearch(int iTimeoutMs)
{
    if (!m_bManualStop)
    {
        m_pSearch->start(iTimeoutMs>0?iTimeoutMs:1000);
    }
}

void MainWindow::slotOnStart()
{
    QString strPath = ui->lineEditPath->text();
    if (strPath.isEmpty())
    {
        QDir dirDefault(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation));
        const QString strDefaultPath = QDir::toNativeSeparators(dirDefault.absoluteFilePath("VX500"));
        if (dirDefault.mkpath(strDefaultPath))
        {
            m_strSaveDir = strDefaultPath;
        }
        else
        {
            QMessageBox::critical(this, "error", "Failed to create the directory for saving pictures. Pictures may not be saved.");
            return;
        }
    }
    else
    {
        QDir dir(strPath);
        if (dir.exists())
        {
            m_strSaveDir = strPath;
        }
        else
        {
            if (dir.mkpath(dir.absolutePath()))
            {
                m_strSaveDir = strPath;
            }
            else
            {
                QMessageBox::critical(this, "error", "Failed to create the path. Please check whether the path is correct.");
                return;
            }
        }
    }
    m_bManualStop = false;
    m_pSearch->start(100);
    ui->btnSelect->setEnabled(false);
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
    LogConsole()<<"Connecting...";
}

void MainWindow::slotOnStop()
{
    m_bManualStop = true;
    m_pSearch->stop();
    if (m_bVideoStarting)
    {
        slotStopVideo();
    }
    if (m_bCameraOpened)
    {
        slotCloseCamera();
    }
    else
    {
        LogConsole()<<"Stopped!!!";
        ui->btnSelect->setEnabled(true);
        ui->btnStart->setEnabled(true);
        ui->btnStop->setEnabled(false);
    }
}

void MainWindow::slotOnSelect()
{
    QString strDir = QFileDialog::getExistingDirectory();
    if (strDir.isEmpty())
    {
        return ;
    }
    ui->lineEditPath->setText(strDir);
}

void MainWindow::slotConnected()
{
    qDebug()<<"the client has connected!";
}

void MainWindow::slotDisconnected()
{
    qDebug()<<"the client has disconnected!";
    m_pTimerReconnect->start(1000);
}

void MainWindow::slotReconnected()
{
    m_pWSClient->open(QUrl(QString("ws://127.0.0.1:%1").arg(WEBSOCKET_SERVER_PORT)));
}

void MainWindow::slotError(QAbstractSocket::SocketError)
{
    qDebug()<<"the client has occurred a error:"<<m_pWSClient->errorString();
    m_pTimerReconnect->start(1000);
}

MainWindow& MainWindow::operator<<(const QString& strLog)
{
    QString str = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    str += ">>";
    str += strLog;
    slotAppendLog(str);
    return *this;
}

void MainWindow::slotTextRecv(const QString& strMsg)
{
    CMessageResponse response;
    if (!response.CJsonMessage::fromJson(strMsg)) return;
    switch (response.getId())
    {
    case REQID_SEARCH:
        parseSearchCamera(response);
        break;
    case REQID_OPEN:
        parseOpenCamera(response);
        break;
    case REQID_CLOSE:
        paraseCloseCamera(response);
        break;
    case REQID_START:
        parseStartVideo(response);
        break;
    case REQID_STOP:
        parseStopVideo(response);
        break;
    }
}

void MainWindow::slotSearchCamera()
{
    CMessageRequest request;
    CSearchCameraRequestParams param;
    request.setId(ReqIDMapper::REQID_SEARCH);
    request.setMethod("dobot.smartcamera.search");
    request.setParams(param.toJsonObject());
    if (m_pWSClient->isValid())
    {
        m_pWSClient->sendTextMessage(request.toJsonString());
    }
    qDebug()<<"Searching for camera...\n";
}

void MainWindow::parseSearchCamera(const CMessageResponse& response)
{
    CSearchCameraResponseResult data;
    data.fromJson(response.getResult());
    if (data.m_data.isEmpty())
    {
        qDebug()<<"No camera found.\n";
        if (!m_strCurrentIdentify.isEmpty())
        {
            LogConsole()<<"The camera is offline and needs to be searched again and reconnected.";
            if (m_bVideoStarting)
            {
                slotStopVideo();
            }
            if (m_bCameraOpened)
            {
                slotCloseCamera();
            }
            m_strCurrentIdentify = "";
            startResearch(3000);
        }
        else
        {
            startResearch(1000);
        }
    }
    else
    {
        CSearchCameraResponseBean bean = data.m_data.takeFirst();
        if (bean.accessible)
        {
            if (!m_strCurrentIdentify.isEmpty() && m_strCurrentIdentify!=bean.identify)
            {//这种情况说明相机被更换了
                qDebug()<<"the camera has changed";
            }
            if (m_strCurrentIdentify.isEmpty())
            {//当前相机为空，则赋值后连接
                m_strCurrentIdentify = bean.identify;
                slotOpenCamera();
            }
            startResearch(3000);
        }
        else if (isSameNetworkSegment(bean.ip,bean.netcardinfo.ip))
        {
            qDebug()<<"The camera is occupied and cannot be used.\n";
            startResearch(1000);
        }
        else
        {
            qDebug()<<"Please set the camera IP to the same network segment.\n";
            startResearch(1000);
        }
    }
}

void MainWindow::slotOpenCamera()
{
    CMessageRequest request;
    COpenCameraRequestParams param;
    param.m_data.identify = m_strCurrentIdentify;
    param.m_data.password = "Abc1234";
    request.setId(ReqIDMapper::REQID_OPEN);
    request.setMethod("dobot.smartcamera.open");
    request.setParams(param.toJsonObject());
    if (m_pWSClient->isValid())
    {
        m_pWSClient->sendTextMessage(request.toJsonString());
    }
    LogConsole()<<"Start connecting to camera...";
}

void MainWindow::parseOpenCamera(const CMessageResponse& response)
{
    if (response.getCode() != ErrorType::DT_NO_ERROR)
    {
        LogConsole()<<"Failed to connect to camera.";
        m_strCurrentIdentify = "";
        return;
    }
    COpenCameraResponseResult data;
    data.fromJson(response.getResult());
    LogConsole()<<"Camera connected successfully.";
    m_bCameraOpened = true;
    slotStartVideo();
}

void MainWindow::slotCloseCamera()
{
    CMessageRequest request;
    CCloseCameraRequestParams param;
    param.m_data.identify = m_strCurrentIdentify;
    request.setId(ReqIDMapper::REQID_CLOSE);
    request.setMethod("dobot.smartcamera.close");
    request.setParams(param.toJsonObject());
    if (m_pWSClient->isValid())
    {
        m_pWSClient->sendTextMessage(request.toJsonString());
    }
    LogConsole()<<"Start disconnecting camera...";
}

void MainWindow::paraseCloseCamera(const CMessageResponse& response)
{
    if (m_bManualStop)
    {
        ui->btnSelect->setEnabled(true);
        ui->btnStart->setEnabled(true);
        ui->btnStop->setEnabled(false);
    }
    m_bCameraOpened = false;
    m_strCurrentIdentify = "";

    if (response.getCode() != ErrorType::DT_NO_ERROR)
    {
        LogConsole()<<"Failed to disconnect camera.";
        return;
    }
    CCloseCameraResponseResult data;
    data.fromJson(response.getResult());
    LogConsole()<<"Camera disconnected successfully.";
    if (ui->btnStop->isEnabled())
    {
        LogConsole()<<"Connecting...";
    }
}

void MainWindow::slotStartVideo()
{
    CMessageRequest request;
    CStartVideoImageRequestParams param;
    param.m_data.identify = m_strCurrentIdentify;
    param.m_data.saveDir = m_strSaveDir;
    request.setId(ReqIDMapper::REQID_START);
    request.setMethod("dobot.smartcamera.startVideoImage");
    request.setParams(param.toJsonObject());
    if (m_pWSClient->isValid())
    {
        m_pWSClient->sendTextMessage(request.toJsonString());
    }
    LogConsole()<<"Start transferring and saving pictures...";
}

void MainWindow::parseStartVideo(const CMessageResponse& response)
{
    if (response.getCode() != ErrorType::DT_NO_ERROR)
    {
        LogConsole()<<"Failed to transfer and save pictures.";
        return;
    }
    CStartVideoImageResponseResult data;
    data.fromJson(response.getResult());
    if (!m_bVideoStarting)
    {
        LogConsole()<<"Start transferring and saving pictures successfully.";
        LogConsole()<<"Transferring and Saving pictures...";
    }
    m_bVideoStarting = true;
}

void MainWindow::slotStopVideo()
{
    m_bVideoStarting = false;
    /*
    CMessageRequest request;
    CStopVideoRequestParams param;
    param.m_data.identify = m_strCurrentIdentify;
    request.setId(ReqIDMapper::REQID_STOP);
    request.setMethod("dobot.smartcamera.stopVideo");
    request.setParams(param.toJsonObject());
    if (m_pWSClient->isValid())
    {
        m_pWSClient->sendTextMessage(request.toJsonString());
    }
    LogConsole()<<"Stop transferring and saving pictures...";
    */
}

void MainWindow::parseStopVideo(const CMessageResponse& response)
{
    if (response.getCode() != ErrorType::DT_NO_ERROR)
    {
        LogConsole()<<"Failed to stop transfer and save pictures.";
        return;
    }
    CStopVideoResponseResult data;
    data.fromJson(response.getResult());
    LogConsole()<<"Stop transferring and saving pictures successfully.";
    m_bVideoStarting = false;
}
