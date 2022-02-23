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
    connect(broker, &ClientBroker::receivedErrorMessage, this, &MainWindow::onErrorRecived);
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

void MainWindow::signIntoPage(const QString &pageName)
{
        if (pageName == "shipper")
        {
            mainPage = new SellerPage(broker, this);
        }
        else if (pageName == "forwarder")
        {
            mainPage = new ForwarderPage(broker, this);
        }
        else if (pageName == "driver")
        {
            mainPage = new DriverPage(broker, this);
        }
        else
        {
            // error?
        }
        ui->stackedWidget->insertWidget(mainPageIndex, mainPage);
        ui->stackedWidget->setCurrentIndex(mainPageIndex);
}

void MainWindow::onErrorRecived(const QString& errorMessage)
{
    QMessageBox::critical(this, QLatin1String("Error!"), errorMessage);
}
