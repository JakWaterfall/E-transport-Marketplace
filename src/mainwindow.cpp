#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(loginIndex);

    broker = new ClientBroker();

    connect(broker, &ClientBroker::signInToPage, this, &MainWindow::signIntoPage);
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

void MainWindow::signIntoPage(QString pageName)
{
        if (pageName == "shipper")
        {
            mainPage = new SellerPage(broker, this);
        }
        else if (pageName == "forwarder")
        {
            mainPage = new ForwarderPage(broker, this);
        }
        else
        {
            // error?
        }
        ui->stackedWidget->insertWidget(mainPageIndex, mainPage);
        ui->stackedWidget->setCurrentIndex(mainPageIndex);
}
