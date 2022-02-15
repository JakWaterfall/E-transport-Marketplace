#ifndef SHIPPERCONTEXT_H
#define SHIPPERCONTEXT_H

#include "controller.h"
#include "shipper.h"

class ShipperController : public Controller
{
    Q_OBJECT
public:
    ShipperController(Shipper* user, ServerBroker* broker, QObject *parent = nullptr);
    // make new order? put it in shipper class?
    //

private:
    Shipper* user;
};

#endif // SHIPPERCONTEXT_H
