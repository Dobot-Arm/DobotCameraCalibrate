#ifndef CPLUGINMANAGER_H
#define CPLUGINMANAGER_H

#include <QObject>
#include <QJsonObject>
#include <QHash>

struct PluginManagerPrivate;
class CMessageRequest;

class CPluginManager : public QObject
{
    Q_OBJECT
public:
    explicit CPluginManager(QObject *parent = nullptr);
    ~CPluginManager();

signals:
    void signalDoResponseMsg(const QJsonObject& obj);

public:
    //send msg to only one plugin
    void sendDoRequestMsg(const CMessageRequest& obj);
    //send msg to all plugin
    void sendAllRequestMsg(const CMessageRequest& obj);

private:
    PluginManagerPrivate* loadPlugin(const QString& strPluginName);
    void unloadAllPlugin();
    void unloadPlugin(const QString& strPluginName, PluginManagerPrivate* ptr);
    void doErrorResponse(const CMessageRequest& request, int iErrorCode);

private:
    QHash<QString, //plugin name: dobot.xxx.
        PluginManagerPrivate*
    > m_allPlugins;
};

#endif // CPLUGINMANAGER_H
