#include "driverpage.h"
#include "ui_driverpage.h"

DriverPage::DriverPage(ClientBroker *broker, QWidget *parent) :
    Page(broker, parent),
    ui(new Ui::DriverPage)
{
    ui->setupUi(this);
    ui->driverWindow->setCurrentIndex(homePage);

    setupDeliveryComboBox();
    connect(broker, &ClientBroker::ordersReceived, this, &DriverPage::processOrderContracts);
    connect(broker, &ClientBroker::marketReceived, this, &DriverPage::processMarket);
    refreshOrders(); // get orders on login
    refreshMarket();
}

DriverPage::~DriverPage()
{
    delete ui;
}

void DriverPage::setupDeliveryComboBox()
{
    ui->deliveryStateComboBox_Delivery->addItems(OrderContract::DeliveryStateToString.values());
}

void DriverPage::setupJobOfferPage(const QString &orderID)
{
    ui->driverWindow->setCurrentIndex(jobOfferPage);

    OrderContract contract = cashedMarket.value(orderID);
    Order order = contract.getOrder();

    ui->descEdit_JobOffer->setText(order.getDescription());
    ui->otherDetailsEdit_JobOffer->setPlainText(order.getOtherDetails());
    ui->widthSpinBox_JobOffer->setValue(order.getWidth());
    ui->heightSpinBox_JobOffer->setValue(order.getHeight());
    ui->depthSpinBox_JobOffer->setValue(order.getDepth());
    ui->weightSpinBox_JobOffer->setValue(order.getWeight());
    ui->fragileEdit_JobOffer->setText(order.isFragile() ? "True" : "False");
    ui->sourceEdit_JobOffer->setPlainText(order.getSourceAddress());
    ui->destEdit_JobOffer->setPlainText(order.getDestinationAddress());
    ui->sourcePostcodeEdit_JobOffer->setText(order.getSourcePostcode());
    ui->destPostcodeEdit_JobOffer->setText(order.getDestinationPostcode());
    ui->consigneeNameEdit_JobOffer->setText(contract.getConsigneeName());
    ui->consigneeNumEdit_JobOffer->setText(contract.getConsigneeNumber());

//    ui->optionalExtrasEdit_JobOffer->setPlainText(contract.get); maybe put optional extras in??
    ui->driverPriceSpinBox_JobOffer->setValue(contract.getFinalDriverPrice());

    currentlySelectedOrderID = contract.getID(); // cashe ID incase user accepts job
}

void DriverPage::setupOrderDetailsPage(const QString &orderID)
{
    ui->driverWindow->setCurrentIndex(orderDetailsPage);

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
}

void DriverPage::setupDeliveryStatePage()
{
    OrderContract contract = cashedOrderContracts.value(currentlySelectedOrderID);
    ui->deliveryStateEdit_Delivery->setText(OrderContract::DeliveryStateToString[contract.getDeliveryState()]);
}

void DriverPage::processOrderContracts(QMap<QString, OrderContract> &orderContracts)
{
    cashedOrderContracts = orderContracts;
    ui->inInventoryOrdersListWidget_Orders->clear();
    ui->compOrdersListWidget_CompOrders->clear();

    for(auto& orderContract : orderContracts)
    {
        addToListWidget(ui->inInventoryOrdersListWidget_Orders, orderContract.getOrder().getDescription(), orderContract.getID());
    }
}

void DriverPage::processMarket(QMap<QString, OrderContract> &marketOrders)
{
    cashedMarket = marketOrders;
    ui->jobOrdersListWidget_JobBoard->clear();

    for(auto& orderContract : marketOrders)
    {
        addToListWidget(ui->jobOrdersListWidget_JobBoard, orderContract.getOrder().getDescription(), orderContract.getID());
    }
}

void DriverPage::on_homeBtn_clicked()
{
    ui->driverWindow->setCurrentIndex(homePage);
}

void DriverPage::on_refreshBtn_clicked()
{
    refreshMarket();
    refreshOrders();
}

void DriverPage::on_jobBoardBtn_clicked()
{
    refreshMarket();
    ui->driverWindow->setCurrentIndex(jobBoardPage);
}

void DriverPage::on_viewOrderScreenBtn_clicked()
{
    refreshOrders();
    ui->driverWindow->setCurrentIndex(ordersPage);
}

void DriverPage::on_viewCompletedOrderScreenBtn_clicked()
{
    ui->driverWindow->setCurrentIndex(completeOrdersPage);
}

void DriverPage::on_jobOrdersListWidget_JobBoard_itemDoubleClicked(QListWidgetItem *item)
{
    QString ID = item->data(Qt::UserRole).toString();
    setupJobOfferPage(ID);
}

void DriverPage::on_acceptBtn_JobOffer_clicked()
{
    broker->acceptJob(currentlySelectedOrderID);

    refreshMarket();
    ui->driverWindow->setCurrentIndex(jobBoardPage);
}

void DriverPage::on_backBtn_JobOffer_clicked()
{
    refreshMarket();
    ui->driverWindow->setCurrentIndex(jobBoardPage);
}

void DriverPage::on_inInventoryOrdersListWidget_Orders_itemDoubleClicked(QListWidgetItem *item)
{
    QString ID = item->data(Qt::UserRole).toString();
    setupOrderDetailsPage(ID);
}

void DriverPage::on_backBtn_OrderDetails_clicked()
{
    refreshOrders();
    ui->driverWindow->setCurrentIndex(orderDetailsPage);
}

void DriverPage::on_updateDeliveryStateBtn_OrderDetails_clicked()
{
    ui->driverWindow->setCurrentIndex(deliveryStatePage);
    setupDeliveryStatePage();
}

void DriverPage::on_backBtn_Delivery_clicked()
{
    ui->driverWindow->setCurrentIndex(orderDetailsPage);
}

void DriverPage::on_acceptBtn_Delivery_clicked()
{
    QString deliveryStateFromComboBox = ui->deliveryStateComboBox_Delivery->currentText();

    broker->updateDeliveryState(currentlySelectedOrderID, OrderContract::DeliveryStateToString.key(deliveryStateFromComboBox));

    refreshOrders();
    ui->driverWindow->setCurrentIndex(ordersPage);
}
