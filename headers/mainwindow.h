#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "sellerpage.h"
#include "forwarderpage.h"
#include "clientbroker.h"
#include "driverpage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUserTypeComboBox();

private slots:
    void on_loginBtn_clicked();
    void signIntoPage(const QString& pageName);
    void onErrorRecived(const QString& errorMessage);
    void onMessageRecived(const QString& message);

    void on_registerBtn_clicked();

    void on_backRegisterBtn_clicked();

    void on_confirmRegisterBtn_clicked();

    void on_actionLog_out_triggered();

private:
    Ui::MainWindow *ui;
    Page* mainPage = nullptr;
    ClientBroker* broker;

    const int loginIndex = 0;
    const int registerIndex = 1;
    const int mainPageIndex = 2;
};
#endif // MAINWINDOW_H
