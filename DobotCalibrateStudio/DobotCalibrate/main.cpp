#include "MainWindow.h"
#include "Logger.h"
#include "StdAfx.h"

#include <QApplication>
#include <cstdio>
#include <QSharedMemory>
#include <QMessageBox>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(true);

    QHash<QString,QString> argsOptions = StdAfx::parseArguments(app);

    QSharedMemory shared("DobotCalibrate_QSharedMemory_Running");
    if (!shared.create(1))
    {
        printf("the first time to create shared memory fail:%s\n",shared.errorString().toStdString().c_str());
        if (shared.error()==QSharedMemory::AlreadyExists)
        {
            shared.attach();
            shared.detach();
            if (!shared.create(1))
            {
                printf("the second time to create shared memory fail:%s\n",shared.errorString().toStdString().c_str());
                printf("app start fail,because the app is running!!!!!\n");
                if (StdAfx::getParameter(argsOptions,"hide")!="true"){
                    QMessageBox::warning(QApplication::desktop(), "", "The program is already running! \r\nPlease do not open it again!");
                }
                return 0;
            }
        }
    }
    printf("app starting.......\n");

    CLogger::getInstance()->startLogServer();
    CLogger::getInstance()->setLogOnFile(StdAfx::getParameter(argsOptions,"logger")=="true");
    qDebug()<<"app starting........";

    MainWindow w(argsOptions);
    w.setWindowTitle(qApp->applicationName()+QString::asprintf(" V-%s %s",__DATE__,__TIME__));
    if (StdAfx::getParameter(argsOptions,"hide")=="true"){
        w.hide();
    }else{
        w.show();
    }

    int iRet = app.exec();
    qDebug()<<"app finished!!!!";
    CLogger::getInstance()->stopLogServer();

    return iRet;
}
