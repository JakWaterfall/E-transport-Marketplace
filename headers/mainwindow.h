#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QDateTime>
#include <QtWidgets/QMessageBox>
#include <QDebug>
#include <QTcpSocket>

#include "sellerpage.h"
#include "forwarderpage.h"
#include "shipper.h"
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
    void on_actionqwe_triggered();

    void on_pushButton_clicked();
    void signIntoPage(QString pageName);

private:

    Ui::MainWindow *ui;
    QWidget * mainPage = nullptr;
    ClientBroker* broker;

    const int loginIndex = 0;
    const int mainPageIndex = 1;
};
#endif // MAINWINDOW_H
