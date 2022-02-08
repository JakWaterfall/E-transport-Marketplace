#ifndef SHIPPER_H
#define SHIPPER_H

#include "user.h"
#include "order.h"
#include "ordercontract.h"
#include <QObject>
#include <QMap>

class Shipper : public User
{
public:
    Shipper(QString firstName, QString lastName, QString email, QString password, QString address);
    ~Shipper();

    void addPendingOrder(OrderContract* contract);
    const QMap<QString, OrderContract*>& getPendingOrders();

private:
    QMap<QString, OrderContract*> pendingOrders;
    QMap<QString, OrderContract*> compleatedOrders;
};

#endif // SHIPPER_H
