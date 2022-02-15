#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(loginIndex);

    broker = new ClientBroker();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mainPage;
}


void MainWindow::on_loginBtn_clicked()
{
    broker->logInAttempt(ui->emailInput->text(), ui->passInput->text());
    // blank password on attempt.

//    if (ui->usernameInput->text() == "q")
//    {
//        mainPage = new ForwarderPage(Forwarder("Bill", "Bill@email.com", "qwe", "123 church road"), this);
//    }
//    else
//    {
//        mainPage = new SellerPage(Shipper("Jak", "j@email.com", "qwe", "123 church road"), this);
//    }
//    ui->stackedWidget->insertWidget(mainPageIndex, mainPage);
//    ui->stackedWidget->setCurrentIndex(mainPageIndex);
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


void MainWindow::on_pushButton_clicked()
{

}
