#ifndef STDAFX_HEADER_H
#define STDAFX_HEADER_H

#include <QHash>
class QCoreApplication;
class QString;

namespace StdAfx
{
    QHash<QString,QString> parseArguments(const QCoreApplication& app);
    QString getParameter(const QHash<QString,QString>& args, const QString& strName);
};

#endif // STDAFX_H
