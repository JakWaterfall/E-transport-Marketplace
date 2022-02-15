#ifndef FORWARDER_H
#define FORWARDER_H

#include "user.h"
#include "order.h"
#include "ordercontract.h"
#include <QObject>
#include <QMap>

class Forwarder : public User
{
public:
    Forwarder(QString name, QString email, QString password, QString address);
    ~Forwarder();

//    void addPendingOrder(OrderContract* contract);
//    const QMap<QString, OrderContract*>& getPendingOrders();

private:
//    QMap<QString, OrderContract*> pendingOrders;
//    QMap<QString, OrderContract*> compleatedOrders;
};

#endif // FORWARDER_H
