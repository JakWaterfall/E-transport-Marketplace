#ifndef DRIVERPAGE_H
#define DRIVERPAGE_H

#include <QWidget>
#include "page.h"

namespace Ui {
class DriverPage;
}

class DriverPage : public Page
{
    Q_OBJECT

public:
    explicit DriverPage(ClientBroker* broker, QWidget *parent = nullptr);
    ~DriverPage();

private:
    void setupDeliveryComboBox();
    void setupJobOfferPage(const QString& orderID);
    void setupOrderDetailsPage(const QString& orderID);
    void setupDeliveryStatePage();

private slots:
    void processOrderContracts(QMap<QString, OrderContract> &orderContracts);
    void processMarket(QMap<QString, OrderContract> &marketOrders);
    void on_homeBtn_clicked();
    void on_refreshBtn_clicked();
    void on_jobBoardBtn_clicked();
    void on_viewOrderScreenBtn_clicked();
    void on_viewCompletedOrderScreenBtn_clicked();
    void on_jobOrdersListWidget_JobBoard_itemDoubleClicked(QListWidgetItem *item);
    void on_acceptBtn_JobOffer_clicked();
    void on_backBtn_JobOffer_clicked();
    void on_inInventoryOrdersListWidget_Orders_itemDoubleClicked(QListWidgetItem *item);
    void on_backBtn_OrderDetails_clicked();
    void on_updateDeliveryStateBtn_OrderDetails_clicked();
    void on_backBtn_Delivery_clicked();
    void on_acceptBtn_Delivery_clicked();

private:
    Ui::DriverPage *ui;
    QString currentlySelectedOrderID;

    const int homePage = 0;
    const int jobBoardPage = 1;
    const int jobOfferPage = 2;
    const int ordersPage = 3;
    const int completeOrdersPage = 4;
    const int orderDetailsPage = 5;
    const int deliveryStatePage = 6;
};

#endif // DRIVERPAGE_H
