#include <QCoreApplication>
#include <QSharedMemory>
#include <cstdio>
#include "MainWindow.h"
#include "Logger.h"
#include "StdAfx.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

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
                return 0;
            }
        }
    }

    QString strVersion = QString::asprintf("V-%s %s",__DATE__,__TIME__);

    CLogger::getInstance()->startLogServer();
    CLogger::getInstance()->setLogOnFile(StdAfx::getParameter(argsOptions,"logger")=="true");
    qDebug()<<"app starting........"<<strVersion;

    MainWindow w(argsOptions);

    int iRet = app.exec();
    qDebug()<<"app finished!!!!";
    CLogger::getInstance()->stopLogServer();

    return iRet;
}
