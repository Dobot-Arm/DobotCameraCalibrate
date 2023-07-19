#include "StdAfx.h"

#include <QCoreApplication>
#include <QString>
#include <QVariant>

/*
QHash<QString, QString> parseArguments(const QCoreApplication &app)
{
    QHash<QString,QString> argsOptions;
    QStringList args = app.arguments();
    for (int i=1; i<args.size(); ++i,++i)
    {
        if (i+1 < args.size())
        {
            argsOptions.insert(args[i],args[i+1]);
        }
    }
    return argsOptions;
}
*/
QHash<QString, QString> StdAfx::parseArguments(const QCoreApplication &app)
{
    QHash<QString,QString> argsOptions;
    QStringList args = app.arguments();
    if (args.size()<2) return argsOptions;
    QString strParam = args[1];

    /*在浏览器中启动进程时，只能传递一个参数，格式为：dobotcalibrate://logger=true&hide=true/
     * 为了兼容通过进程方式打开该程序，所以按照浏览器的规则去解析数据
    **/
    int iPos = strParam.indexOf("//");
    if (iPos >= 0) strParam = strParam.mid(iPos+2);
    strParam.remove(QChar('/'));
    args = strParam.split(QChar('&'));
    for (int i=0; i<args.size(); ++i)
    {
        QStringList kv = args[i].split(QChar('='));
        if (kv.size()>=2) argsOptions.insert(kv[0],kv[1]);
        else argsOptions.insert(kv[0],"");
    }

    return argsOptions;
}

QString StdAfx::getParameter(const QHash<QString, QString> &args, const QString &strName)
{
    if (args.contains(strName))
    {
        return args.value(strName);
    }
    return "";
}
