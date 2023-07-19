#include "MainWindow.h"
#include "Logger.h"
#include "MessageCenter/MessageCenter.h"

#include <QCoreApplication>
#include <iostream>

MainWindow::MainWindow(QHash<QString,QString> args, QObject *parent)
    : QObject(parent)
    , m_argsOptions(args)
{

    //日志信号槽
    connect(CLogger::getInstance(), &CLogger::signalPrintLogMsg,
            this, &MainWindow::slotAppendLog);

    //start server
    CMessageCenter::getInstance()->start();
    connect(CMessageCenter::getInstance(), &CMessageCenter::signalExitWindow, this, &MainWindow::slotExitApp);
}


MainWindow::~MainWindow()
{
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
    static int iLogCount = 0;
    ++iLogCount;
    if (iLogCount>100)
    {
        slotClearLog();
        iLogCount = 0;
    }
    if (strLog.length()>1024)
    {
        std::cout<<"text is too large, does not print\n";
    }
    else
    {
        std::cout<<strLog.toStdString().c_str()<<'\n';
    }
}

void MainWindow::slotClearLog()
{
}

void MainWindow::slotExitApp()
{
    CMessageCenter::getInstance()->stop();
    CMessageCenter::destroyInstance();
    qApp->quit();
}

void MainWindow::slotActionTest()
{
}
