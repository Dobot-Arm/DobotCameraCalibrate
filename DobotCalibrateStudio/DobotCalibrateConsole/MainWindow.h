#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QHash>

class MainWindow : public QObject
{
    Q_OBJECT
public:
    MainWindow(QHash<QString,QString> args, QObject *parent = nullptr);
    ~MainWindow();

private slots:
    void slotLogOnFile(bool bOn);
    void slotLogOnWnd(bool bOn);
    void slotAppendLog(const QString& strLog);
    void slotClearLog();
    void slotExitApp();

    void slotActionTest();

private:
    const QHash<QString,QString> m_argsOptions;
};

#endif // MAINWINDOW_H
