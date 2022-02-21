#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "sellerpage.h"
#include "forwarderpage.h"
#include "clientbroker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loginBtn_clicked();
    void signIntoPage(const QString& pageName);
    void onErrorRecived(const QString& errorMessage);

private:
    Ui::MainWindow *ui;
    Page* mainPage = nullptr;
    ClientBroker* broker;

    const int loginIndex = 0;
    const int mainPageIndex = 1;
};
#endif // MAINWINDOW_H
