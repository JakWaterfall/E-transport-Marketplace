#include "sellerpage.h"
#include "ui_sellerpage.h"

SellerPage::SellerPage(Shipper user, QWidget *parent) :
    Page(parent),
    ui(new Ui::SellerPage),
    user(user)
{
    ui->setupUi(this);

    ui->sellerWindow->setCurrentIndex(0);

    connect(broker.getClient(), &QMqttClient::messageReceived, this, &SellerPage::onMessageRecived);
    connect(ui->sellerSubmitBtn, &QPushButton::clicked, this, &SellerPage::onSellerSubmitBtn_clicked);


    //connect(&broker, &Broker::newOrderContract, this, &SellerPage::onContractReceieved); // test buyer slot

    //QListWidgetItem* item = new QListWidgetItem("item 1", ui->orderList, QListWidgetItem::UserType);
//    item->setData(Qt::UserRole, s.c_str());
//    ui->orderList->addItem("order1");
}

SellerPage::~SellerPage()
{
    delete ui;
}

void SellerPage::onSellerSubmitBtn_clicked()
{
    Order* order = new Order(ui->sourceEdit->text(), ui->destEdit->text(), ui->dimensionsEdit->text(), ui->weightSpinBox->value(),
                             ui->fragileCheckBox->isChecked(), ui->typeEdit->text());
    //OrderContract * contract = new OrderContract(order, user.getFirstName(), user.getEmail(), "responce/" + order->getID());

   // user.addPendingOrder(contract);

    //broker.sendOrderToMarket(contract);

    //buildListWidget(ui->orderList, user.getPendingOrders());
}


void SellerPage::onMessageRecived(const QByteArray &message, const QMqttTopicName &topic)
{
    const QString mes = "Received Topic: " + topic.name() + " Message: " + message + "\n";
    ui->buyerTextBox->insertPlainText(mes);
}

void SellerPage::subscribe()
{
    qDebug() << "subbed";
//    auto subscription = mqttClient->subscribe(QLatin1String(topic));
//    if (!subscription) {
//        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
//        return;
//    }
    ui->sellerSubmitBtn->setDisabled(false);
}

void SellerPage::on_orderList_itemDoubleClicked(QListWidgetItem *item)
{
    QString orderID = item->data(Qt::UserRole).toString();

    //ui->buyerTextBox->insertPlainText(user.getPendingOrders().value(orderID)->getOrder()->getID() + "\n");
}

void SellerPage::on_homeBtn_clicked()
{
    ui->sellerWindow->setCurrentIndex(0);
}

void SellerPage::on_sendOrderScreenBtn_clicked()
{
    ui->sellerWindow->setCurrentIndex(1);
}
