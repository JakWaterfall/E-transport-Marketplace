#ifndef FORWARDERPAGE_H
#define FORWARDERPAGE_H

#include "page.h"


namespace Ui {
class ForwarderPage;
}

class ForwarderPage : public Page
{
    Q_OBJECT

public:
    explicit ForwarderPage(ClientBroker* broker, QWidget *parent = nullptr);
    ~ForwarderPage();

private:
    void setBidPage(const QString& orderID);
    void setOrderDetailsPage(const QString& orderID);

private slots:
    void on_orderMarketBtn_clicked();

    void on_homeBtn_clicked();

    void on_refreshBtn_clicked();

    void on_viewOrderScreenBtn_clicked();

    void on_viewCompletedOrderScreenBtn_clicked();

    void processOrderContracts(QMap<QString, OrderContract> &orderContracts);

    void processMarket(QMap<QString, OrderContract> &marketOrders);

    void on_backBtn_Bid_clicked();

    void on_makeBidBtn_Bid_clicked();

    void on_marketOrdersListWidget_Market_itemDoubleClicked(QListWidgetItem *item);

    void on_offersMadeListWidget_Orders_itemDoubleClicked(QListWidgetItem *item);

    void on_viewBidBtn_OrderDetails_clicked();

    void on_backBtn_ViewBid_clicked();

    void on_awaitingDeliveryListWidget_Orders_itemDoubleClicked(QListWidgetItem *item);

    void on_backBtn_OrderDetails_clicked();

private:
    Ui::ForwarderPage *ui;
    QString currentlySelectedOrderID;

    const int homePage = 0;
    const int marketPage = 1;
    const int makeBidPage = 2;
    const int ordersPage = 3;
    const int completeOrdersPage = 4;
    const int orderDetailsPage = 5;
    const int viewBidPage = 6;
};

#endif // FORWARDERPAGE_H
