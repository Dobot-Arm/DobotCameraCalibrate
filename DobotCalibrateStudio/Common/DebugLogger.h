#ifndef CDEBUGLOGGER_H
#define CDEBUGLOGGER_H

#include <QTextStream>
#include <QString>
#include <QMessageLogContext>

class CDebugLogger
{
protected:
    const char* m_pszFile;
    const int m_iLine;
    const char* m_pszFunction;

    QTextStream m_ts;
    QString m_buffer;

    bool m_bDebug;
    QtMsgType m_msgType;

public:
    explicit CDebugLogger(const char* pszFile, int iLine, const char* pszFunction);
    CDebugLogger(const CDebugLogger&)=delete;
    CDebugLogger(CDebugLogger&&)=delete;
    CDebugLogger& operator=(const CDebugLogger&)=delete;
    CDebugLogger& operator=(CDebugLogger&&)=delete;
    ~CDebugLogger();

    inline CDebugLogger& debug(){m_msgType=QtMsgType::QtDebugMsg;return *this;}
    inline CDebugLogger& info(){m_msgType=QtMsgType::QtInfoMsg;return *this;}
    inline CDebugLogger& warning(){m_msgType=QtMsgType::QtWarningMsg;return *this;}
    inline CDebugLogger& critical(){m_msgType=QtMsgType::QtCriticalMsg;return *this;}
    inline CDebugLogger& fatal(){m_msgType=QtMsgType::QtFatalMsg;return *this;}

    inline CDebugLogger& setDebug(bool v){ m_bDebug = v;return *this;}

    inline CDebugLogger& operator<<(bool t){ if(m_bDebug){m_ts << (t ? "true" : "false");} return *this;}
    inline CDebugLogger& operator<<(char t){ if(m_bDebug){m_ts << t;} return *this;}
    inline CDebugLogger& operator<<(QChar t) { if(m_bDebug){putUcs4(t.unicode());} return *this; }
    inline CDebugLogger& operator<<(signed short t) { if(m_bDebug){m_ts << t;} return *this; }
    inline CDebugLogger& operator<<(unsigned short t) { if(m_bDebug){m_ts << t;} return *this; }
    inline CDebugLogger& operator<<(char16_t t) { if(m_bDebug){m_ts << QChar(ushort(t));} return *this; }
    inline CDebugLogger& operator<<(char32_t t) { if(m_bDebug){putUcs4(t);} return *this; }
    inline CDebugLogger& operator<<(signed int t) { if(m_bDebug){m_ts << t;} return *this; }
    inline CDebugLogger& operator<<(unsigned int t) { if(m_bDebug){m_ts << t;} return *this; }
    inline CDebugLogger& operator<<(signed long t) { if(m_bDebug){m_ts << t;} return *this; }
    inline CDebugLogger& operator<<(unsigned long t) { if(m_bDebug){m_ts << t;} return *this; }
    inline CDebugLogger& operator<<(qint64 t) { if(m_bDebug){m_ts << t;} return *this; }
    inline CDebugLogger& operator<<(quint64 t) { if(m_bDebug){m_ts << t;} return *this; }
    inline CDebugLogger& operator<<(float t) { if(m_bDebug){m_ts << t;} return *this; }
    inline CDebugLogger& operator<<(double t) { if(m_bDebug){m_ts << t;} return *this; }
    inline CDebugLogger& operator<<(const char* t) { if(m_bDebug){m_ts << QString::fromUtf8(t);} return *this; }
    inline CDebugLogger& operator<<(const QString & t) { if(m_bDebug){m_ts << t;} return *this; }
    inline CDebugLogger& operator<<(const QStringRef & t) { if(m_bDebug){m_ts << t;} return *this; }
    inline CDebugLogger& operator<<(QStringView t) { if(m_bDebug){m_ts << t;} return *this; }
    inline CDebugLogger& operator<<(QLatin1String t) { if(m_bDebug){m_ts << t;} return *this; }
    inline CDebugLogger& operator<<(const QByteArray & t) { if(m_bDebug){m_ts << t;} return *this; }
    inline CDebugLogger& operator<<(const void * t) { if(m_bDebug){m_ts << t;} return *this; }
    inline CDebugLogger& operator<<(std::nullptr_t) { if(m_bDebug){m_ts << "(nullptr)";} return *this; }
    inline CDebugLogger& operator<<(QTextStreamFunction f) { if(m_bDebug){m_ts << f;} return *this;}
    inline CDebugLogger& operator<<(QTextStreamManipulator m){ if(m_bDebug){m_ts << m;} return *this; }

    CDebugLogger& operator<<(const QStringList & t);

private:
    void putUcs4(uint ucs4);
};

#endif // CDEBUGLOGGER_H
