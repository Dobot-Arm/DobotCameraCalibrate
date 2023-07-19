#ifndef HKSMARTCAMERAPLUGIN_H
#define HKSMARTCAMERAPLUGIN_H

#include <DobotInterfacePlugin.h>
#include <QHash>

class CMessageRequest;
class CDobotDevice;
struct HKSmartCameraPluginPrivate;

class HKSmartCameraPlugin : public DobotInterfacePlugin
{
    Q_OBJECT
    Q_INTERFACES(DobotInterfacePlugin)
    Q_PLUGIN_METADATA(IID DobotInterfacePlugin_IID)

public:
    explicit HKSmartCameraPlugin(QObject *parent = nullptr);
    ~HKSmartCameraPlugin() Q_DECL_OVERRIDE;

    QString getVersion() Q_DECL_OVERRIDE;

protected slots:
    void slotDoRequest(QJsonObject obj) Q_DECL_OVERRIDE;

private:
    void doHandlerClientClosed(const CMessageRequest& msg);
    void doHandlerDobotExit(const CMessageRequest& msg);
    void doHandlerCmd(const CMessageRequest& msg);

    CDobotDevice* getDobotDevice(QString strSenderId);
    CDobotDevice* createDobotDeviceIfNotExist(QString strSenderId);
    void deleteDobotDevice(QString strSenderId);

private:
    HKSmartCameraPluginPrivate* m_ptr;
};

#endif // HKSMARTCAMERAPLUGIN_H
