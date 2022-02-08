#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(loginIndex);



//    mqttClient = new QMqttClient(this);
//    mqttClient->setPort(1883);
//    mqttClient->setHostname("test.mosquitto.org");


}

MainWindow::~MainWindow()
{
    delete ui;
//    delete mqttClient;
    delete mainPage;
}


void MainWindow::on_loginBtn_clicked()
{
    if (ui->usernameInput->text() == "q")
    {
        mainPage = new ForwarderPage(Forwarder("Bill", "Thompson", "Bill@email.com", "qwe", "123 church road"), this);
    }
    else
    {
        mainPage = new SellerPage(Shipper("Jak", "Waterfall", "j@email.com", "qwe", "123 church road"), this);
    }
    ui->stackedWidget->insertWidget(mainPageIndex, mainPage);
    ui->stackedWidget->setCurrentIndex(mainPageIndex);
}

void MainWindow::on_actionqwe_triggered()
{
    if (mainPage)
    {
        delete mainPage;
        ui->stackedWidget->removeWidget(mainPage);
        mainPage = nullptr;
    }
}

