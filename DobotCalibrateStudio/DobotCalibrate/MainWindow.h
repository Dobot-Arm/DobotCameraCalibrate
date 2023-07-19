#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QHash>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QHash<QString,QString> args, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent*) Q_DECL_OVERRIDE;

    void enableAdvFirewall();

private slots:
    void slotLogOnFile(bool bOn);
    void slotLogOnWnd(bool bOn);
    void slotAppendLog(const QString& strLog);
    void slotClearLog();
    void slotExitApp();

    void slotActionTest();

private:
    Ui::MainWindow *ui;
    int m_iLogCount = 0;
    const QHash<QString,QString> m_argsOptions;
};
#endif // MAINWINDOW_H
