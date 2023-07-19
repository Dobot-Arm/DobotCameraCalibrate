#ifndef CMESSAGECENTERPRIVATE_H
#define CMESSAGECENTERPRIVATE_H

#include <QObject>
#include <QEventLoop>

class CMessageCenterPrivate : public QObject
{
    Q_OBJECT
public:
    explicit CMessageCenterPrivate(QObject* parent=nullptr):QObject(parent){};

signals:
    void signalStart(bool* pIsFinished, bool* pResult);
    void signalStop(bool* pIsFinished);
};

#endif // CMESSAGECENTERPRIVATE_H
