#ifndef DOBOTINTERFACEPLUGIN_H
#define DOBOTINTERFACEPLUGIN_H

#ifdef DOBOT_INTERFACEPLUGIN_CLASS_LIBRARY
#define API_DOBOT_INTERFACEPLUGIN_EXPORT Q_DECL_EXPORT
#else
#define API_DOBOT_INTERFACEPLUGIN_EXPORT Q_DECL_IMPORT
#endif

#include <QObject>
#include <QtGlobal>
#include <QJsonObject>

class DobotInterfacePluginPrivate;
class API_DOBOT_INTERFACEPLUGIN_EXPORT DobotInterfacePlugin : public QObject
{
    Q_OBJECT
public:
    explicit DobotInterfacePlugin(QObject *parent = nullptr);
    virtual ~DobotInterfacePlugin();

    virtual QString getVersion() {return "";};

    void doRequestMsg(const QJsonObject& obj);

signals:
    void signalDoResponse(QJsonObject obj,QPrivateSignal);

protected slots:
    virtual void slotDoRequest(QJsonObject obj) = 0;

protected:
    void doResponseMsg(const QJsonObject& obj);

private:
    DobotInterfacePluginPrivate* m_ptr;
};

#define DobotInterfacePlugin_IID "com.dobot.dobotinterfaceplugin.iid"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(DobotInterfacePlugin, DobotInterfacePlugin_IID)
QT_END_NAMESPACE

#endif // DOBOTINTERFACEPLUGIN_H
