#include "sellerpage.h"
#include "ui_sellerpage.h"

#include "QStandardItemModel"

SellerPage::SellerPage(ClientBroker *broker, QWidget *parent) :
    Page(broker, parent),
    ui(new Ui::SellerPage)
{
    ui->setupUi(this);

    ui->sellerWindow->setCurrentIndex(0);

    connect(ui->sellerSubmitBtn, &QPushButton::clicked, this, &SellerPage::onSellerSubmitBtn_clicked);
    connect(broker, &ClientBroker::pendingOrderReceived, this, &SellerPage::addOrderDetialsToOrderView);

    //QListWidgetItem* item = new QListWidgetItem("item 1", ui->orderList, QListWidgetItem::UserType);
//    item->setData(Qt::UserRole, s.c_str());
//    ui->orderList->addItem("order1");

//    QStandardItemModel* model = new QStandardItemModel(4,1);
//    for (auto i = 0; i < 2; i++) {
//        QStandardItem * itam = new QStandardItem(QString("Name: %0, ID: %1").arg("my order").arg("qweewqqweewq"));
//        model->setItem(i, itam);
//    }
//    ui->listView->setModel(model);

}

SellerPage::~SellerPage()
{
    delete ui;
}

void SellerPage::onSellerSubmitBtn_clicked()
{
    Order order(ui->sourceEdit->text(), ui->destEdit->text(), ui->dimensionsEdit->text(), ui->weightSpinBox->value(),
                             ui->fragileCheckBox->isChecked(), ui->typeEdit->text());
    OrderContract * contract = new OrderContract(order);

    broker->sendOrderToMarketplace(contract);

    delete contract;
}


void SellerPage::onMessageRecived(const QByteArray &message, const QMqttTopicName &topic)
{
    const QString mes = "Received Topic: " + topic.name() + " Message: " + message + "\n";
    //ui->buyerTextBox->insertPlainText(mes);
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


void SellerPage::on_viewOrderScreenBtn_clicked()
{
    ui->sellerWindow->setCurrentIndex(2);
    ui->pendingOrdersListWidget->clear();
    broker->buildOrderScreen();
}

void SellerPage::addOrderDetialsToOrderView(QVector<OrderContract> orderContracts)
{
    for(auto& order : orderContracts)
    {
        addToListWidget(ui->pendingOrdersListWidget, order.getShipperEmail(), order.getID());
    }

}
