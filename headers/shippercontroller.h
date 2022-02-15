#ifndef SHIPPERCONTEXT_H
#define SHIPPERCONTEXT_H

#include "controller.h"
#include "shipper.h"

class ShipperController : public Controller
{
    Q_OBJECT
public:
    ShipperController(Shipper* user, ServerBroker* broker, QObject *parent = nullptr);
    ~ShipperController();

private slots:
    void makeNewOrder();

private:
    Shipper* user;
};

#endif // SHIPPERCONTEXT_H
