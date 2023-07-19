#include "PluginManager.h"
#include "DError.h"
#include "JsonMessage.h"
#include "NullDataBean.h"
#include "DobotInterfacePlugin.h"

#include <QPluginLoader>
#include <QThread>

struct PluginManagerPrivate
{
    QPluginLoader* pLoader;
    DobotInterfacePlugin* pInterface;
    QThread* pThd;

    PluginManagerPrivate()
    {
        pLoader = nullptr;
        pInterface = nullptr;
        pThd = nullptr;
    }
    ~PluginManagerPrivate()
    {
        if (pLoader) pLoader->deleteLater();
        if (pThd) pThd->deleteLater();
    }
};

CPluginManager::CPluginManager(QObject *parent) : QObject(parent)
{
}

CPluginManager::~CPluginManager()
{
    unloadAllPlugin();
}

#define CREATE_PLUGIN_MGR_MICRO(pluginName, pluginLibrary)                             \
if (pluginName == strPluginName){                                                      \
    auto pLoader = new QPluginLoader(pluginLibrary, this);                             \
    if (!pLoader->load()){                                                             \
        qCritical()<<pluginLibrary<<" load error:"<<pLoader->errorString();            \
        pLoader->deleteLater();                                                        \
        return nullptr;                                                                \
    }                                                                                  \
    QObject* pInstance = pLoader->instance();                                          \
    if (!pInstance){                                                                   \
        qCritical()<<pluginLibrary<<" plugin new instance is nullptr";                 \
        pLoader->unload();                                                             \
        pLoader->deleteLater();                                                        \
        return nullptr;                                                                \
    }                                                                                  \
    DobotInterfacePlugin* pInterface = qobject_cast<DobotInterfacePlugin*>(pInstance); \
    if (!pInterface){                                                                  \
        qCritical()<<pluginLibrary<<" plugin is not inhert DobotInterfacePlugin";      \
        pLoader->unload();                                                             \
        pLoader->deleteLater();                                                        \
        return nullptr;                                                                \
    }                                                                                  \
    qDebug()<<pluginName<<" Version is "<<pInterface->getVersion();                    \
    QThread* pThd = new QThread();                                                     \
    pInterface->moveToThread(pThd);                                                    \
    auto pPluginMgr = new PluginManagerPrivate;                                        \
    pPluginMgr->pLoader = pLoader;                                                     \
    pPluginMgr->pInterface = pInterface;                                               \
    pPluginMgr->pThd = pThd;                                                           \
    m_allPlugins.insert(strPluginName, pPluginMgr);                                    \
    connect(pInterface, &DobotInterfacePlugin::signalDoResponse,                       \
            this, &CPluginManager::signalDoResponseMsg);                               \
    pThd->start();                                                                     \
    return pPluginMgr;                                                                 \
}

PluginManagerPrivate* CPluginManager::loadPlugin(const QString& strPluginName)
{
    CREATE_PLUGIN_MGR_MICRO("dobot.camera","HKIndustrialCameraPlugin")
    CREATE_PLUGIN_MGR_MICRO("dobot.ioctrldevice","HKIndustrialIOControllerPlugin")
    CREATE_PLUGIN_MGR_MICRO("dobot.smartcamera","HKSmartCameraPlugin")
    return nullptr;
}

void CPluginManager::unloadAllPlugin()
{
    while (!m_allPlugins.isEmpty())
    {
        QString strPluginName = m_allPlugins.begin().key();
        PluginManagerPrivate* ptr = m_allPlugins.take(strPluginName);
        unloadPlugin(strPluginName, ptr);
    }
}

void CPluginManager::unloadPlugin(const QString& strPluginName, PluginManagerPrivate *ptr)
{
    if (ptr->pThd->isRunning())
    {
        ptr->pLoader->unload();
        ptr->pThd->quit();
        ptr->pThd->terminate();
        if (ptr->pThd->wait(1000))
        {
            qInfo()<<strPluginName<<" plugin has already unload!";
        }
        else
        {
            qWarning()<<strPluginName<<" plugin may not have been completely unload!!!";
        }
    }
    delete ptr;
}

void CPluginManager::sendDoRequestMsg(const CMessageRequest& request)
{
    const QString strPluginName = request.getPluginName();
    if (strPluginName.isEmpty())
    {
        qCritical()<<"the request plugin name can not empty.";
        doErrorResponse(request, DT_ERR_INVALID_PLUGIN);
        return ;
    }

    PluginManagerPrivate* pPlugin = nullptr;
    if (m_allPlugins.contains(strPluginName))
    {
        pPlugin = m_allPlugins.value(strPluginName);
    }
    else
    {
        pPlugin = loadPlugin(strPluginName);
        if (!pPlugin)
        {
            qCritical()<<"load plugin failed,plugin name:"<<strPluginName;
            doErrorResponse(request, DT_ERR_INVALID_PLUGIN);
            return ;
        }
    }
    pPlugin->pInterface->doRequestMsg(request.toJsonObject());

    return ;
}

void CPluginManager::sendAllRequestMsg(const CMessageRequest& request)
{
    QJsonObject obj = request.toJsonObject();
    for(auto itr = m_allPlugins.begin(); itr != m_allPlugins.end(); ++itr)
    {
        auto pPlugin = itr.value();
        pPlugin->pInterface->doRequestMsg(obj);
    }

    return ;
}

void CPluginManager::doErrorResponse(const CMessageRequest &request, int iErrorCode)
{
    CNullDataBean result;
    CMessageResponse res(request);
    res.setCode(iErrorCode);
    res.setErrMsg(DError::getErrMsg(iErrorCode));
    res.setResult(result.toJsonObject());

    emit signalDoResponseMsg(res.toJsonObject());

    return ;
}
