#ifndef DRIVERPAGE_H
#define DRIVERPAGE_H

#include <QWidget>
#include "page.h"

namespace Ui {
class DriverPage;
}

/**
 * @brief The DriverPage class holds all the logic for the Driver client side view.
 */
class DriverPage : public Page
{
    Q_OBJECT

public:
    /**
     * @brief DriverPage Constructor
     * @param broker The Message broker for the client.
     * @param parent The parent object for QT Framework.
     */
    explicit DriverPage(ClientBroker* broker, QWidget *parent = nullptr);
    ~DriverPage();

private:
    /**
     * @brief Sets up the Delivery state combo box with all possible delivery states in string form.
     */
    void setupDeliveryComboBox();

    /**
     * @brief Sets up job offer page with infomation from a order.
     * @param orderID The ID of the order used.
     */
    void setupJobOfferPage(const QString& orderID);

    /**
     * @brief Sets up the order details screen with the data from an order.
     * @param orderID The ID of the order.
     */
    void setupOrderDetailsPage(const QString& orderID);

    /**
     * @brief Sets up delivery state page with data from the currently selected order contract.
     */
    void setupDeliveryStatePage();

private slots:
    /**
     * @brief Processes and places order contracts into the correct list widget for display.
     * @param orderContracts The order contracts.
     */
    void processOrderContracts(QMap<QString, OrderContract> &orderContracts);

    /**
     * @brief Processes and places marketplace orders into the Job Board list widget for display.
     * @param marketOrders The order contracts from the marketplace.
     */
    void processMarket(QMap<QString, OrderContract> &marketOrders);

    /**
     * @brief Opens the home page.
     */
    void on_homeBtn_clicked();

    /**
     * @brief Triggers request from the server to refreash the users related order contracts and the marketplace Job Board orders.
     */
    void on_refreshBtn_clicked();

    /**
     * @brief Opens Job Board Page.
     */
    void on_jobBoardBtn_clicked();

    /**
     * @brief Opens orders page.
     */
    void on_viewOrderScreenBtn_clicked();

    /**
     * @brief Opens completed Orders Page.
     */
    void on_viewCompletedOrderScreenBtn_clicked();

    /**
     * @brief Opens up the job offer page with order that was double clicked on from the Job Orders list widget.
     * @param item The list widget item that has the order infomation.
     */
    void on_jobOrdersListWidget_JobBoard_itemDoubleClicked(QListWidgetItem *item);

    /**
     * @brief Sends message to server to accept a job offer.
     */
    void on_acceptBtn_JobOffer_clicked();

    /**
     * @brief Returns back to the job board page from the job offer pafe.
     */
    void on_backBtn_JobOffer_clicked();

    /**
     * @brief Opens up the order details page with order that was double clicked on from the In Inventory Orders list widget.
     * @param item The list widget item that has the order infomation.
     */
    void on_inInventoryOrdersListWidget_Orders_itemDoubleClicked(QListWidgetItem *item);

    /**
     * @brief Returns back to the orders page from the order details page.
     */
    void on_backBtn_OrderDetails_clicked();

    /**
     * @brief Opens the delivery state page.
     */
    void on_updateDeliveryStateBtn_OrderDetails_clicked();

    /**
     * @brief Returns back to the order details page from the delivery state page.
     */
    void on_backBtn_Delivery_clicked();

    /**
     * @brief Sends to the server a update to the delivery state of the currently selected order.
     */
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
