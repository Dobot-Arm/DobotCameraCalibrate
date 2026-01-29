#ifndef DOBOTCONTROLLERPLUGIN_H
#define DOBOTCONTROLLERPLUGIN_H

#include <DobotInterfacePlugin.h>

class CMessageRequest;
struct DobotControllerPluginPrivate;

class DobotControllerPlugin : public DobotInterfacePlugin
{
    Q_OBJECT
    Q_INTERFACES(DobotInterfacePlugin)
    Q_PLUGIN_METADATA(IID DobotInterfacePlugin_IID)

public:
    explicit DobotControllerPlugin(QObject *parent = nullptr);
    ~DobotControllerPlugin() Q_DECL_OVERRIDE;

    QString getVersion() Q_DECL_OVERRIDE;

protected slots:
    void slotDoRequest(QJsonObject obj) Q_DECL_OVERRIDE;

private:
    void doHandlerClientClosed(const CMessageRequest& msg);
    void doHandlerDobotExit(const CMessageRequest& msg);
    void doHandlerCmd(const CMessageRequest& msg);

private:
    DobotControllerPluginPrivate* m_ptr;
};

#endif // DOBOTCONTROLLERPLUGIN_H
