#ifndef SELLERPAGE_H
#define SELLERPAGE_H

#include "page.h"

namespace Ui {
class SellerPage;
}

/**
 * @brief The SellerPage class holds all the logic for the Shippers client side view.
 */
class SellerPage : public Page
{
    Q_OBJECT

public:
    /**
     * @brief SellerPage Constructor.
     * @param broker The Message broker for the client.
     * @param parent The parent object for QT Framework.
     */
    explicit SellerPage(ClientBroker* broker, QWidget *parent = nullptr);
    ~SellerPage();

private:
    /**
     * @brief Clears the new order screen of any remaining information in the widgets.
     */
    void clearNewOrderScreen();

    /**
     * @brief Sets up the order details screen with the data from an order.
     * @param orderID The ID of the order.
     */
    void setupOrderDetailsPage(const QString& orderID);

    /**
     * @brief Sets up the bid page with the bid data from an order.
     * @param orderID The ID of the order.
     */
    void setupBidsPage(const QString& orderID);

    /**
     * @brief Caluclates the shipping rate in the new order screen based on the source and destination postcodes.
     */
    void calculateShippingRate();

private slots:
    /**
     * @brief Sets the current window to the home page.
     */
    void on_homeBtn_clicked();

    /**
     * @brief Sets the current window to the new orderpage.
     */
    void on_sendOrderScreenBtn_clicked();

    /**
     * @brief Sets the current window to the view order page.
     */
    void on_viewOrderScreenBtn_clicked();

    /**
     * @brief Processes and places order contracts into the correct list widget for display.
     * @param orderContracts The order contracts.
     */
    void processOrderContracts(QMap<QString, OrderContract> &orderContracts);

    /**
     * @brief Triggers request from the server to refreash the users related order contracts.
     */
    void on_refreshBtn_clicked();

    /**
     * @brief Sets the current window to the view completed orders page.
     */
    void on_viewCompletedOrderScreenBtn_clicked();

    /**
     * @brief Creates a new order from the infomation provided by the user and sends it to the marketplace.
     */
    void on_submitBtn_NewOrder_clicked();

    /**
     * @brief Opens up the order details page with order that was double clicked on from the Awaiting Bids list widget.
     * @param item The list widget item that has the order infomation.
     */
    void on_awaitingBidsListWidget_Orders_itemDoubleClicked(QListWidgetItem *item);

    /**
     * @brief Returns the user back to the home page from the order details page.
     */
    void on_backBtn_OrderDetails_clicked();

    /**
     * @brief Opens up the order details page with the order that was double clicked on from the Awaiting Delivery list widget.
     * @param item The list widget item that has the order infomation.
     */
    void on_awaitingDeliveryListWidget_Orders_itemDoubleClicked(QListWidgetItem *item);

    /**
     * @brief Opens up the order details page with the order that was double clicked on from the Completed Orders list widget.
     * @param item The list widget item that has the order infomation.
     */
    void on_compOrdersListWidget_CompOrders_itemDoubleClicked(QListWidgetItem *item);

    /**
     * @brief Opens up the View Bids page with the bids from the currently selected order.
     */
    void on_viewBidsBtn_OrderDetails_clicked();

    /**
     * @brief Loads the bid from the order into the GUI for the user to see. Also enables the accept bid button.
     * @param item The list widget item that has the bid index for locating the bid in the order.
     */
    void on_bidsListWidget_Bids_itemClicked(QListWidgetItem *item);

    /**
     * @brief Returns to the order details page from the bids page.
     */
    void on_backBtn_Bids_clicked();

    /**
     * @brief Sends a message to the server to accept the currently selected bid on an order.
     */
    void on_acceptBtn_Bids_clicked();

    /**
     * @brief Triggers the calculate shipping rate when the user changes the source postcode.
     * @param arg1
     */
    void on_sourcePostcodeComboBox_NewOrder_activated(const QString &arg1);

    /**
     * @brief Triggers the calculate shipping rate when the user changes the destination postcode.
     * @param arg1
     */
    void on_destPostcodeComboBox_NewOrder_activated(const QString &arg1);

private:
    Ui::SellerPage *ui;
    QVector<QLineEdit*> newOrderLineEdits;
    QVector<QPlainTextEdit*> newOrderPlainTextEdits;
    QVector<QDoubleSpinBox*> newOrderSpinBoxes;

    QVector<QLineEdit*> orderDetailsLineEdits;
    QVector<QPlainTextEdit*> orderDetailsPlainTextEdits;
    QVector<QDoubleSpinBox*> orderDetailsSpinBoxes;

    QString currentlySelectedOrderID;
    OrderContract::Bid currentlySelectedBid;

    const int homePage = 0;
    const int makeOrderPage = 1;
    const int viewPendingOrderPage = 2;
    const int viewCompletedOrderPage = 3;
    const int orderDetailsPage = 4;
    const int bidsPage = 5;
};

#endif // SELLERPAGE_H
