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
    connect(broker, &ClientBroker::receivedMessage, this, &MainWindow::onMessageRecived);

    setupUserTypeComboBox();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mainPage;
}

void MainWindow::setupUserTypeComboBox()
{
    ui->UserTypeRegistercomboBox->addItems({"Shipper", "Forwarder", "Driver"});
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

void MainWindow::onMessageRecived(const QString &message)
{
    QMessageBox::information(this, QLatin1String("Infomation!"), message);
}

void MainWindow::on_registerBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(registerIndex);
}

void MainWindow::on_backRegisterBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(loginIndex);
}

void MainWindow::on_confirmRegisterBtn_clicked()
{
    // Send Register attempt
    QString name = ui->nameRegisterlineEdit->text();
    QString email = ui->EmailRegisterlineEdit->text();
    QString password = ui->PassRegisterlineEdit->text();
    QString confirmPass = ui->confirmPassRegisterlineEdit->text();
    QString address = ui->AddressRegisterTextEdit->toPlainText();
    QString postcode = ui->postcodeRegisterlineEdit->text();
    QString userType = ui->UserTypeRegistercomboBox->currentText();

    broker->registerAttempt(name, email, password, confirmPass, address, postcode, userType);
}

void MainWindow::on_actionLog_out_triggered()
{
    ui->stackedWidget->setCurrentIndex(loginIndex);

    if(mainPage)
    {
        ui->stackedWidget->removeWidget(mainPage);
        delete mainPage;
        mainPage = nullptr;
    }

    if(broker)
    {
        delete broker;
        broker = new ClientBroker();
        connect(broker, &ClientBroker::signInToPage, this, &MainWindow::signIntoPage);
        connect(broker, &ClientBroker::receivedErrorMessage, this, &MainWindow::onErrorRecived);
        connect(broker, &ClientBroker::receivedMessage, this, &MainWindow::onMessageRecived);
    }
}
