#include "forwarderpage.h"
#include "ui_forwarderpage.h"

ForwarderPage::ForwarderPage(ClientBroker *broker, QWidget *parent) :
    Page(broker, parent),
    ui(new Ui::ForwarderPage)
{
    ui->setupUi(this);
    ui->forwarderWindow->setCurrentIndex(homePage);

    connect(broker, &ClientBroker::ordersReceived, this, &ForwarderPage::processOrderContracts);
    connect(broker, &ClientBroker::marketReceived, this, &ForwarderPage::processMarket);
    refreshOrders(); // get orders on login
    refreshMarket();

}

ForwarderPage::~ForwarderPage()
{
    delete ui;
}

void ForwarderPage::setupBidPage(const QString &orderID)
{
    // clear old bid
    ui->bidAmountSpinBox_Bid->setValue(0.0);
    ui->driverPriceSpinBox_Bid->setValue(0.0);
    ui->optionalExtrasEdit_Bid->clear();

    ui->forwarderWindow->setCurrentIndex(makeBidPage);

    OrderContract contract = cashedMarket.value(orderID);
    Order order = contract.getOrder();

    ui->descEdit_Bid->setText(order.getDescription());
    ui->otherDetailsEdit_Bid->setPlainText(order.getOtherDetails());
    ui->widthSpinBox_Bid->setValue(order.getWidth());
    ui->heightSpinBox_Bid->setValue(order.getHeight());
    ui->depthSpinBox_Bid->setValue(order.getDepth());
    ui->weightSpinBox_Bid->setValue(order.getWeight());
    ui->fragileEdit_Bid->setText(order.isFragile() ? "True" : "False");
    ui->sourceEdit_Bid->setPlainText(order.getSourceAddress());
    ui->destEdit_Bid->setPlainText(order.getDestinationAddress());
    ui->sourcePostcodeEdit_Bid->setText(order.getSourcePostcode());
    ui->destPostcodeEdit_Bid->setText(order.getDestinationPostcode());
    ui->consigneeNameEdit_Bid->setText(contract.getConsigneeName());
    ui->consigneeNumEdit_Bid->setText(contract.getConsigneeNumber());

    currentlySelectedOrderID = contract.getID(); // cashe ID incase user makes a bid.
}

void ForwarderPage::setupOrderDetailsPage(const QString &orderID)
{
    ui->forwarderWindow->setCurrentIndex(orderDetailsPage);

    OrderContract contract = cashedOrderContracts.value(orderID);
    Order order = contract.getOrder();

    currentlySelectedOrderID = orderID;

    //Disable view bid button if the order is no longer on the market and therefore the forwarders bid was already accepted
    ui->viewBidBtn_OrderDetails->setDisabled(contract.getState() != OrderContract::State::onMarket ? true : false);

    ui->descEdit_OrderDetails->setText(order.getDescription());
    ui->otherDetailsEdit_OrderDetails->setPlainText(order.getOtherDetails());
    ui->widthSpinBox_OrderDetails->setValue(order.getWidth());
    ui->heightSpinBox_OrderDetails->setValue(order.getHeight());
    ui->depthSpinBox_OrderDetails->setValue(order.getDepth());
    ui->weightSpinBox_OrderDetails->setValue(order.getWeight());
    ui->fragileEdit_OrderDetails->setText(order.isFragile() ? "True" : "False");
    ui->sourceEdit_OrderDetails->setPlainText(order.getSourceAddress());
    ui->destEdit_OrderDetails->setPlainText(order.getDestinationAddress());
    ui->sourcePostcodeEdit_OrderDetails->setText(order.getSourcePostcode());
    ui->destPostcodeEdit_OrderDetails->setText(order.getDestinationPostcode());
    ui->consigneeNameEdit_OrderDetails->setText(contract.getConsigneeName());
    ui->consigneeNumEdit_OrderDetails->setText(contract.getConsigneeNumber());
    ui->shipperEmailEdit_OrderDetails->setText(contract.getShipperEmail());
    ui->forwarderEmailEdit_OrderDetails->setText(contract.getForwarderEmail());
    ui->driverEmailEdit_OrderDetails->setText(contract.getDriverEmail());
    ui->finalPriceSpinBox_OrderDetails->setValue(contract.getFinalBid());
    ui->orderStateEdit_OrderDetails->setText(OrderContract::stateToString[contract.getState()]);
    ui->deliveryStateEdit_OrderDetails->setText(OrderContract::DeliveryStateToString[contract.getDeliveryState()]);
}

void ForwarderPage::on_orderMarketBtn_clicked()
{
    refreshMarket();
    ui->forwarderWindow->setCurrentIndex(marketPage);
}

void ForwarderPage::on_homeBtn_clicked()
{
    ui->forwarderWindow->setCurrentIndex(homePage);
}

void ForwarderPage::on_refreshBtn_clicked()
{
    refreshMarket();
    refreshOrders();
}

void ForwarderPage::on_viewOrderScreenBtn_clicked()
{
    refreshOrders();
    ui->forwarderWindow->setCurrentIndex(ordersPage);
}

void ForwarderPage::on_viewCompletedOrderScreenBtn_clicked()
{
    ui->forwarderWindow->setCurrentIndex(completeOrdersPage);
}

void ForwarderPage::processOrderContracts(QMap<QString, OrderContract> &orderContracts)
{
    cashedOrderContracts = orderContracts;
    ui->offersMadeListWidget_Orders->clear();
    ui->awaitingDeliveryListWidget_Orders->clear();
    ui->compOrdersListWidget_CompOrders->clear();

    for(auto& orderContract : orderContracts)
    {
        switch (orderContract.getState())
        {
        case OrderContract::State::onMarket:
            addToListWidget(ui->offersMadeListWidget_Orders, orderContract.getOrder().getDescription(), orderContract.getID());
            break;

        case OrderContract::State::inForwarderInventory:
        case OrderContract::State::inDriverInventory:
            addToListWidget(ui->awaitingDeliveryListWidget_Orders, orderContract.getOrder().getDescription(), orderContract.getID());
            break;
        }
    }
}

void ForwarderPage::processMarket(QMap<QString, OrderContract> &marketOrders)
{
    cashedMarket = marketOrders;
    ui->marketOrdersListWidget_Market->clear();

    for(auto& orderContract : marketOrders)
    {
        addToListWidget(ui->marketOrdersListWidget_Market, orderContract.getOrder().getDescription(), orderContract.getID());
    }
}

void ForwarderPage::on_backBtn_Bid_clicked()
{
    ui->forwarderWindow->setCurrentIndex(marketPage);
}

void ForwarderPage::on_makeBidBtn_Bid_clicked()
{
    OrderContract::Bid bid = {ui->optionalExtrasEdit_Bid->toPlainText(), ui->bidAmountSpinBox_Bid->value(), ui->driverPriceSpinBox_Bid->value()};
    broker->makeBidOnOrder(currentlySelectedOrderID, bid);
    refreshMarket();
    ui->forwarderWindow->setCurrentIndex(marketPage);
}

void ForwarderPage::on_marketOrdersListWidget_Market_itemDoubleClicked(QListWidgetItem *item)
{
    QString ID = item->data(Qt::UserRole).toString();
    setupBidPage(ID);
}

void ForwarderPage::on_offersMadeListWidget_Orders_itemDoubleClicked(QListWidgetItem *item)
{
    QString ID = item->data(Qt::UserRole).toString();
    setupOrderDetailsPage(ID);
}

void ForwarderPage::on_viewBidBtn_OrderDetails_clicked()
{
    ui->forwarderWindow->setCurrentIndex(viewBidPage);
    OrderContract contract = cashedOrderContracts[currentlySelectedOrderID];
    OrderContract::Bid bid = contract.getBids().at(0);

    ui->bidPriceSpinBox_ViewBid->setValue(bid.amount);
    ui->optionalExtrasEdit_ViewBid->setPlainText(bid.optionalExtras);
}

void ForwarderPage::on_backBtn_ViewBid_clicked()
{
    ui->forwarderWindow->setCurrentIndex(orderDetailsPage);
}

void ForwarderPage::on_awaitingDeliveryListWidget_Orders_itemDoubleClicked(QListWidgetItem *item)
{
    QString ID = item->data(Qt::UserRole).toString();
    setupOrderDetailsPage(ID);
}

void ForwarderPage::on_backBtn_OrderDetails_clicked()
{
    ui->forwarderWindow->setCurrentIndex(ordersPage);
}
