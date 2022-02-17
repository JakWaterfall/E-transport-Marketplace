#ifndef SELLERPAGE_H
#define SELLERPAGE_H

#include "page.h"
#include <QWidget>
#include <QtMqtt/QtMqtt>
#include <QtCore/QDateTime>
#include <QtMqtt/QMqttClient>
#include <QListWidgetItem>
#include <QtWidgets/QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QMap>

#include <string>
#include "order.h"
#include "shipper.h"
//#include "broker.h"


namespace Ui {
class SellerPage;
}

class SellerPage : public Page
{
    Q_OBJECT

public:
    explicit SellerPage(ClientBroker* broker, QWidget *parent = nullptr);
    ~SellerPage();


private slots:
    void onSellerSubmitBtn_clicked();

    void onMessageRecived(const QByteArray &message, const QMqttTopicName &topic);
    void subscribe();

    void on_orderList_itemDoubleClicked(QListWidgetItem *item);

    void on_homeBtn_clicked();

    void on_sendOrderScreenBtn_clicked();

    void on_viewOrderScreenBtn_clicked();

    void addOrderDetialsToOrderView(const QString& name, const QString& ID);

private:
    Ui::SellerPage *ui;
};

#endif // SELLERPAGE_H
