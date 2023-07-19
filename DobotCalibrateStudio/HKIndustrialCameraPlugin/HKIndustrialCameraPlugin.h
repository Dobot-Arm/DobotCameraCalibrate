#ifndef HKINDUSTRIALCAMERAPLUGIN_H
#define HKINDUSTRIALCAMERAPLUGIN_H

#include <DobotInterfacePlugin.h>
#include <QHash>

class CMessageRequest;
class CDobotDevice;
struct HKIndustrialCameraPluginPrivate;

class HKIndustrialCameraPlugin : public DobotInterfacePlugin
{
    Q_OBJECT
    Q_INTERFACES(DobotInterfacePlugin)
    Q_PLUGIN_METADATA(IID DobotInterfacePlugin_IID)

public:
    explicit HKIndustrialCameraPlugin(QObject *parent = nullptr);
    ~HKIndustrialCameraPlugin() Q_DECL_OVERRIDE;

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
    HKIndustrialCameraPluginPrivate* m_ptr;
};

#endif // HKINDUSTRIALCAMERAPLUGIN_H
