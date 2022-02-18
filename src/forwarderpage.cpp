#include "forwarderpage.h"
#include "ui_forwarderpage.h"

ForwarderPage::ForwarderPage(ClientBroker *broker, QWidget *parent) :
    Page(broker, parent),
    ui(new Ui::ForwarderPage)
{
    ui->setupUi(this);

    ui->forwarderWindow->setCurrentIndex(0);

//    broker.subscribeToTopic("OrderMarket/");
//    connect(broker.getClient(), &QMqttClient::connected, this, [this]() {
//        broker.subscribeToTopic("OrderMarket/");
//    });
//    connect(&broker, &Broker::newOrderContract, this, &ForwarderPage::onNewOrderContract);
}

ForwarderPage::~ForwarderPage()
{
    delete ui;
}

void ForwarderPage::setupBidPage(OrderContract *contract)
{
    //ui->shipperNameLineEdit->setText(contract->getSellerName());
    ui->shipperEmailLineEdit->setText(contract->getShipperEmail());
//    const Order order = contract->getOrder();
//    ui->typeLineEdit->setText(order->getType());
//    ui->dimensionsLineEdit->setText(order->getDismensions());
//    ui->weightSpinBox->setValue(order->getWeight());
//    ui->createdAtLineEdit->setText(order->getCreationDate().toString("dd/MM/yyyy"));
//    ui->fragileLineEdit->setText(order->isFragile() ? "True" : "False");
//    ui->sourceTextEdit->setPlainText(order->getSourceAddress());
//    ui->destinationTextEdit->setPlainText(order->getDestinationAddress());
    ui->forwarderWindow->setCurrentIndex(bidPage);
}

void ForwarderPage::on_homeScreenBtn_clicked()
{
    ui->forwarderWindow->setCurrentIndex(homePage);
}

void ForwarderPage::on_orderMarketList_itemDoubleClicked(QListWidgetItem *item)
{
//    QString orderID = item->data(Qt::UserRole).toString();
//    OrderContract* contract = marketOrderContracts[orderID];
//    setupBidPage(contract);
}

void ForwarderPage::onNewOrderContract(OrderContract *contract)
{
    //marketOrderContracts.insert(contract->getOrder()->getID(), contract);
//    buildListWidget(ui->orderMarketList, marketOrderContracts);
}

void ForwarderPage::on_orderMarketBtn_clicked()
{
    ui->forwarderWindow->setCurrentIndex(marketPage);
}
