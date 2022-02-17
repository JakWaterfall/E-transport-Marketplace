#ifndef FORWARDERPAGE_H
#define FORWARDERPAGE_H

#include <QWidget>
#include <QListWidgetItem>

#include "page.h"
#include "forwarder.h"
#include "ordercontract.h"
#include "order.h"

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
    void setupBidPage(OrderContract * contract);

private slots:
    void on_homeScreenBtn_clicked();
    void on_orderMarketList_itemDoubleClicked(QListWidgetItem *item);
    void onNewOrderContract(OrderContract * contract);
    void on_orderMarketBtn_clicked();

private:
    Ui::ForwarderPage *ui;
//    QMap<QString, OrderContract*> marketOrderContracts;

    const int homePage = 0;
    const int marketPage = 1;
    const int bidPage = 2;
};

#endif // FORWARDERPAGE_H
