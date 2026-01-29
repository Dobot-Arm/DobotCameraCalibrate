#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QHash>
#include <QWebSocket>
#include <QTimer>
#include "JsonMessage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent*) Q_DECL_OVERRIDE;
    void enableAdvFirewall();
    void startResearch(int iTimeoutMs);

    enum ReqIDMapper
    {
        REQID_SEARCH = 1,
        REQID_OPEN,
        REQID_CLOSE,
        REQID_START,
        REQID_STOP
    };
    void parseSearchCamera(const CMessageResponse& response);
    void parseOpenCamera(const CMessageResponse& response);
    void paraseCloseCamera(const CMessageResponse& response);
    void parseStartVideo(const CMessageResponse& response);
    void parseStopVideo(const CMessageResponse& response);

    MainWindow& operator<<(const QString& strLog);

private slots:
    void slotExitApp();
    void slotAppendLog(const QString& strLog);
    void slotOnStart();
    void slotOnStop();
    void slotOnSelect();
    void slotConnected();
    void slotDisconnected();
    void slotReconnected();
    void slotError(QAbstractSocket::SocketError erro);
    void slotTextRecv(const QString& strMsg);

    void slotSearchCamera();
    void slotOpenCamera();
    void slotCloseCamera();
    void slotStartVideo();
    void slotStopVideo();

private:
    Ui::MainWindow *ui;
    int m_iLogCount = 0;
    QWebSocket* m_pWSClient;
    QTimer* m_pTimerReconnect;
    QTimer* m_pSearch;
    QString m_strCurrentIdentify;
    QString m_strSaveDir;

    bool m_bManualStop = false;
    bool m_bCameraOpened = false;
    bool m_bVideoStarting = false;
};
#endif // MAINWINDOW_H
