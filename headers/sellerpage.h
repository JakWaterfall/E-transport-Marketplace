#ifndef SELLERPAGE_H
#define SELLERPAGE_H

#include "page.h"

namespace Ui {
class SellerPage;
}

class SellerPage : public Page
{
    Q_OBJECT

public:
    explicit SellerPage(ClientBroker* broker, QWidget *parent = nullptr);
    ~SellerPage();

private:
    void clearNewOrderScreen();
    void setOrderDetailsPage(const QString& orderID);
    void setBidsPage(const QString& orderID);

private slots:
    void on_homeBtn_clicked();
    void on_sendOrderScreenBtn_clicked();
    void on_viewOrderScreenBtn_clicked();
    void processOrderContracts(QMap<QString, OrderContract> &orderContracts);
    void on_refreshBtn_clicked();
    void on_viewCompletedOrderScreenBtn_clicked();
    void on_submitBtn_NewOrder_clicked();
    void on_awaitingBidsListWidget_Orders_itemDoubleClicked(QListWidgetItem *item);
    void on_backBtn_OrderDetails_clicked();

    void on_awaitingDeliveryListWidget_Orders_itemDoubleClicked(QListWidgetItem *item);

    void on_compOrdersListWidget_CompOrders_itemDoubleClicked(QListWidgetItem *item);

    void on_viewBidsBtn_OrderDetails_clicked();

    void on_bidsListWidget_Bids_itemClicked(QListWidgetItem *item);

    void on_backBtn_Bids_clicked();

    void on_acceptBtn_Bids_clicked();

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
