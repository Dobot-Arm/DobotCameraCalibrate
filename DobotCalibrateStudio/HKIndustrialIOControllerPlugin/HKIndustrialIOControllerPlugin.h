#ifndef HKINDUSTRIALIOCONTROLLERPLUGIN_H
#define HKINDUSTRIALIOCONTROLLERPLUGIN_H

#include <DobotInterfacePlugin.h>
#include <QHash>
#include <QSet>

class CMessageRequest;
class CDobotDevice;
struct HKIndustrialIOControllerPluginPrivate;

class HKIndustrialIOControllerPlugin : public DobotInterfacePlugin
{
    Q_OBJECT
    Q_INTERFACES(DobotInterfacePlugin)
    Q_PLUGIN_METADATA(IID DobotInterfacePlugin_IID)

public:
    explicit HKIndustrialIOControllerPlugin(QObject *parent = nullptr);
    ~HKIndustrialIOControllerPlugin() Q_DECL_OVERRIDE;

    QString getVersion() Q_DECL_OVERRIDE;

protected slots:
    void slotDoRequest(QJsonObject obj) Q_DECL_OVERRIDE;
    void slotRecvDeviceMsg(QJsonObject obj);

private:
    void doHandlerClientClosed(const CMessageRequest& msg);
    void doHandlerDobotExit(const CMessageRequest& msg);
    void doHandlerCmd(const CMessageRequest& msg);

    void eraseDeviceIfNotOpen(CDobotDevice* pDobotDevice, QString strSenderId);

private:
    HKIndustrialIOControllerPluginPrivate* m_ptr;
};

#endif // HKINDUSTRIALIOCONTROLLERPLUGIN_H
