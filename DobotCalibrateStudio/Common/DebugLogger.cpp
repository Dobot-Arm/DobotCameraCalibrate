#include "DebugLogger.h"
#include <QMutex>

CDebugLogger::CDebugLogger(const char *pszFile, int iLine, const char *pszFunction)
    :m_pszFile(pszFile),m_iLine(iLine),m_pszFunction(pszFunction)
{
    m_ts.setString(&m_buffer, QIODevice::WriteOnly);
    m_bDebug = true;
}

CDebugLogger::~CDebugLogger()
{
    if (m_bDebug)
    {
        qt_message_output(m_msgType, QMessageLogContext(m_pszFile, m_iLine, m_pszFunction, nullptr), m_buffer);
    }
}

void CDebugLogger::putUcs4(uint ucs4)
{
    if (ucs4 < 0x20) {
        m_ts << "\\x" << hex << ucs4 << reset;
    } else if (ucs4 < 0x80) {
        m_ts << char(ucs4);
    } else {
        if (ucs4 < 0x10000)
            m_ts << "\\u" << qSetFieldWidth(4);
        else
            m_ts << "\\U" << qSetFieldWidth(8);
        m_ts << hex << qSetPadChar(QLatin1Char('0')) << ucs4 << reset;
    }
}

CDebugLogger& CDebugLogger::operator<<(const QStringList & t)
{
    QString strApp="[";
    for(QString str : t)
    {
        strApp += QString("%1,").arg(str);
    }
    strApp += "]";
    this->operator<<(strApp);
    return *this;
}
