#include "sellerpage.h"
#include "ui_sellerpage.h"

#include "QStandardItemModel"

SellerPage::SellerPage(ClientBroker *broker, QWidget *parent) :
    Page(broker, parent),
    ui(new Ui::SellerPage)
{
    ui->setupUi(this);

    // put edits into own function
    newOrderLineEdits = QVector({ui->descEdit_NewOrder, ui->sourcePostcodeEdit_NewOrder, ui->destPostcodeEdit_NewOrder, ui->consigneeNameEdit_NewOrder, ui->consigneeNumEdit_NewOrder});
    newOrderSpinBoxes = QVector ({ui->widthSpinBox_NewOrder, ui->heightSpinBox_NewOrder, ui->depthSpinBox_NewOrder, ui->weightSpinBox_NewOrder});
    newOrderPlainTextEdits = QVector({ui->sourceEdit_NewOrder, ui->destEdit_NewOrder, ui->otherDetailsEdit_NewOrder});

    orderDetailsLineEdits = QVector({ui->descEdit_OrderDetails,
                                     ui->fragileEdit_OrderDetails,
                                     ui->sourcePostcodeEdit_OrderDetails,
                                     ui->destPostcodeEdit_OrderDetails,
                                     ui->consigneeNameEdit_OrderDetails,
                                     ui->consigneeNumEdit_OrderDetails,
                                     ui->shipperEmailEdit_OrderDetails,
                                     ui->forwarderEmailEdit_OrderDetails,
                                     ui->driverEmailEdit_OrderDetails,
                                     ui->orderStateEdit_OrderDetails,
                                     ui->deliveryStateEdit_OrderDetails});

    orderDetailsPlainTextEdits = QVector({ui->otherDetailsEdit_OrderDetails, ui->sourceEdit_OrderDetails, ui->destEdit_OrderDetails});
    orderDetailsSpinBoxes = QVector({ui->widthSpinBox_OrderDetails, ui->heightSpinBox_OrderDetails, ui->depthSpinBox_OrderDetails, ui->weightSpinBox_OrderDetails, ui->finalPriceSpinBox_OrderDetails});

    ui->sellerWindow->setCurrentIndex(homePage);

    ui->sourcePostcodeComboBox_NewOrder->addItems(postcodeToPoint.keys());
    ui->destPostcodeComboBox_NewOrder->addItems(postcodeToPoint.keys());
    calculateShippingRate();

    connect(broker, &ClientBroker::ordersReceived, this, &SellerPage::processOrderContracts);
    refreshOrders(); // get orders on login
}

SellerPage::~SellerPage()
{
    delete ui;
}

void SellerPage::clearNewOrderScreen()
{
    ui->fragileCheckBox_NewOrder->setChecked(false);
    clearAssortedWidgets(newOrderLineEdits, newOrderPlainTextEdits, newOrderSpinBoxes);
}

void SellerPage::setupOrderDetailsPage(const QString &orderID)
{
    ui->sellerWindow->setCurrentIndex(orderDetailsPage);

    OrderContract contract = cashedOrderContracts.value(orderID);
    Order order = contract.getOrder();

    currentlySelectedOrderID = orderID;

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

    if(contract.getBids().isEmpty())
        ui->viewBidsBtn_OrderDetails->setDisabled(true);
    else
        ui->viewBidsBtn_OrderDetails->setDisabled(false);
}

void SellerPage::on_homeBtn_clicked()
{
    ui->sellerWindow->setCurrentIndex(homePage);
}

void SellerPage::on_sendOrderScreenBtn_clicked()
{
    ui->sellerWindow->setCurrentIndex(makeOrderPage);
}


void SellerPage::on_viewOrderScreenBtn_clicked()
{
    ui->sellerWindow->setCurrentIndex(viewPendingOrderPage);
    refreshOrders();
}

void SellerPage::processOrderContracts(QMap<QString, OrderContract>& orderContracts)
{
    cashedOrderContracts = orderContracts;
    ui->awaitingBidsListWidget_Orders->clear();
    ui->awaitingDeliveryListWidget_Orders->clear();
    ui->compOrdersListWidget_CompOrders->clear();

    for(auto& orderContract : orderContracts)
    {
        switch (orderContract.getState())
        {
        case OrderContract::State::onMarket:
            addToListWidget(ui->awaitingBidsListWidget_Orders, orderContract.getOrder().getDescription(), orderContract.getID());
            break;

        case OrderContract::State::inForwarderInventory:
        case OrderContract::State::inDriverInventory:
            addToListWidget(ui->awaitingDeliveryListWidget_Orders, orderContract.getOrder().getDescription(), orderContract.getID());
            break;
        }
    }
}

void SellerPage::on_refreshBtn_clicked()
{
    refreshOrders();
}

void SellerPage::on_viewCompletedOrderScreenBtn_clicked()
{
    ui->sellerWindow->setCurrentIndex(viewCompletedOrderPage);
}

void SellerPage::on_submitBtn_NewOrder_clicked()
{
    Order order(ui->descEdit_NewOrder->text(),
                ui->sourceEdit_NewOrder->toPlainText(),
                ui->destEdit_NewOrder->toPlainText(),
                ui->sourcePostcodeComboBox_NewOrder->currentText() + ui->sourcePostcodeEdit_NewOrder->text(),
                ui->destPostcodeComboBox_NewOrder->currentText() + ui->destPostcodeEdit_NewOrder->text(),
                ui->otherDetailsEdit_NewOrder->toPlainText(),
                ui->widthSpinBox_NewOrder->value(),
                ui->heightSpinBox_NewOrder->value(),
                ui->depthSpinBox_NewOrder->value(),
                ui->weightSpinBox_NewOrder->value(),
                ui->fragileCheckBox_NewOrder->isChecked());

    OrderContract contract(order,
                           ui->consigneeNameEdit_NewOrder->text(),
                           ui->consigneeNumEdit_NewOrder->text());

    broker->sendOrderToMarketplace(contract);

    clearNewOrderScreen();
}

void SellerPage::on_awaitingBidsListWidget_Orders_itemDoubleClicked(QListWidgetItem *item)
{
    QString ID = item->data(Qt::UserRole).toString();
    setupOrderDetailsPage(ID);
}

void SellerPage::on_backBtn_OrderDetails_clicked()
{
    ui->sellerWindow->setCurrentIndex(homePage);
}

void SellerPage::on_awaitingDeliveryListWidget_Orders_itemDoubleClicked(QListWidgetItem *item)
{
    QString ID = item->data(Qt::UserRole).toString();
    setupOrderDetailsPage(ID);
}

void SellerPage::on_compOrdersListWidget_CompOrders_itemDoubleClicked(QListWidgetItem *item)
{
    QString ID = item->data(Qt::UserRole).toString();
    setupOrderDetailsPage(ID);
}

void SellerPage::on_viewBidsBtn_OrderDetails_clicked()
{
    ui->sellerWindow->setCurrentIndex(bidsPage);
    setupBidsPage(currentlySelectedOrderID);
}

void SellerPage::setupBidsPage(const QString &orderID)
{
    ui->sellerWindow->setCurrentIndex(bidsPage);

    // clear previous bids
    ui->bidsListWidget_Bids->clear();
    ui->bidPriceSpinBox_Bids->setValue(0.0);
    ui->optionalExtrasEdit_Bids->clear();

    // disable accept button until bid is selected
    ui->acceptBtn_Bids->setDisabled(true);

    OrderContract contract = cashedOrderContracts[orderID];
    const QVector<OrderContract::Bid>& bids = contract.getBids();

    for(int index = 0; index < contract.getBids().size(); index++)
    {
        addToListWidget(ui->bidsListWidget_Bids, bids[index].forwarderEmail, index);
    }
}

void SellerPage::calculateShippingRate()
{
    auto source = ui->sourcePostcodeComboBox_NewOrder->currentText();
    auto destination = ui->destPostcodeComboBox_NewOrder->currentText();
    ui->shippingRateSpinBox_NewOrder->setValue(getShippingRate(source, destination));
}

void SellerPage::on_bidsListWidget_Bids_itemClicked(QListWidgetItem *item)
{
    int bidIndex = item->data(Qt::UserRole).toInt();

    // enable accept button
    ui->acceptBtn_Bids->setDisabled(false);

    OrderContract contract = cashedOrderContracts[currentlySelectedOrderID];
    const QVector<OrderContract::Bid>& bids = contract.getBids();

    currentlySelectedBid = bids.at(bidIndex);

    ui->bidPriceSpinBox_Bids->setValue(currentlySelectedBid.amount);
    ui->optionalExtrasEdit_Bids->setPlainText(currentlySelectedBid.optionalExtras);
}

void SellerPage::on_acceptBtn_Bids_clicked()
{
    broker->sendAcceptBidMessage(currentlySelectedOrderID, currentlySelectedBid);
    refreshOrders();
    setupOrderDetailsPage(currentlySelectedOrderID);
}

void SellerPage::on_backBtn_Bids_clicked()
{
    ui->sellerWindow->setCurrentIndex(orderDetailsPage);
}

void SellerPage::on_sourcePostcodeComboBox_NewOrder_activated(const QString &arg1)
{
    calculateShippingRate();
}

void SellerPage::on_destPostcodeComboBox_NewOrder_activated(const QString &arg1)
{
    calculateShippingRate();
}
