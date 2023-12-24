#ifndef FORWARDERPAGE_H
#define FORWARDERPAGE_H

#include "page.h"


namespace Ui {
class ForwarderPage;
}

/**
 * @brief The ForwarderPage class holds all the logic for the Forwarder client side view.
 */
class ForwarderPage : public Page
{
    Q_OBJECT

public:
    /**
     * @brief ForwarderPage Constructor.
     * @param broker The Message broker for the client.
     * @param parent The parent object for QT Framework.
     */
    explicit ForwarderPage(ClientBroker* broker, QWidget *parent = nullptr);
    ~ForwarderPage();

private:
    /**
     * @brief Sets up bid page with an order for the forwarder to place a bid.
     * @param orderID The ID of the order.
     */
    void setupBidPage(const QString& orderID);

    /**
     * @brief Sets up the order details screen with the data from an order.
     * @param orderID The ID of the order.
     */
    void setupOrderDetailsPage(const QString& orderID);

private slots:
    /**
     * @brief Opens the marketplace window.
     */
    void on_orderMarketBtn_clicked();

    /**
     * @brief Opens the home page window.
     */
    void on_homeBtn_clicked();

    /**
     * @brief Triggers request from the server to refreash the users related order contracts and the marketplace orders.
     */
    void on_refreshBtn_clicked();

    /**
     * @brief Opens orders screen window.
     */
    void on_viewOrderScreenBtn_clicked();

    /**
     * @brief Opens completed orders screen window.
     */
    void on_viewCompletedOrderScreenBtn_clicked();

    /**
     * @brief Processes and places order contracts into the correct list widget for display.
     * @param orderContracts The order contracts.
     */
    void processOrderContracts(QMap<QString, OrderContract> &orderContracts);

    /**
     * @brief Processes and places marketplace orders into the marketplace list widget for display.
     * @param marketOrders The order contracts from the marketplace.
     */
    void processMarket(QMap<QString, OrderContract> &marketOrders);

    /**
     * @brief Retruns back to the marketplace window from the bids page.
     */
    void on_backBtn_Bid_clicked();

    /**
     * @brief Creates a Bid from the infomation provided by the user and sends it to be placed on the currently selected order in the marketplace.
     */
    void on_makeBidBtn_Bid_clicked();

    /**
     * @brief Opens up the bid page with order that was double clicked on from the Marketplace Orders list widget.
     * @param item The list widget item that has the order infomation.
     */
    void on_marketOrdersListWidget_Market_itemDoubleClicked(QListWidgetItem *item);

    /**
     * @brief Opens up the order details page with order that was double clicked on from the Offers Made list widget.
     * @param item The list widget item that has the order infomation.
     */
    void on_offersMadeListWidget_Orders_itemDoubleClicked(QListWidgetItem *item);

    /**
     * @brief Opens up the view bid page for the user to view thier current bid on an order.
     */
    void on_viewBidBtn_OrderDetails_clicked();

    /**
     * @brief Returns back to the order details page from the view bid page.
     */
    void on_backBtn_ViewBid_clicked();

    /**
     * @brief Opens up the order details page with order that was double clicked on from the Awaiting Delivery list widget.
     * @param item The list widget item that has the order infomation.
     */
    void on_awaitingDeliveryListWidget_Orders_itemDoubleClicked(QListWidgetItem *item);

    /**
     * @brief Returns back to the orders page from the order details page.
     */
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
