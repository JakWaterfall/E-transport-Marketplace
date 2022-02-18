#ifndef SHIPPERCONTEXT_H
#define SHIPPERCONTEXT_H

#include "controller.h"
#include "shipper.h"

class ShipperController : public Controller
{
    Q_OBJECT
public:
    ShipperController(Shipper* user, ServerBroker* broker, ThreadSafeMap<QString, OrderContract *> *marketplace, QObject *parent = nullptr);
    ~ShipperController();

private slots:
    void makeNewOrder(OrderContract * orderContract);
    void sendOrderDetails();

private:
    Shipper* user;
};

#endif // SHIPPERCONTEXT_H
