#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMqtt/QtMqtt>
#include <QtCore/QDateTime>
#include <QtMqtt/QMqttClient>
#include <QtWidgets/QMessageBox>
#include <QDebug>

#include "sellerpage.h"
#include "forwarderpage.h"
#include "shipper.h"

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

private:

    Ui::MainWindow *ui;
//    QMqttClient *mqttClient;
    QWidget * mainPage = nullptr;

    const int loginIndex = 0;
    const int mainPageIndex = 1;
};
#endif // MAINWINDOW_H
