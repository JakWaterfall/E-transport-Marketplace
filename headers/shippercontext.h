#ifndef SHIPPERCONTEXT_H
#define SHIPPERCONTEXT_H

#include "context.h"
#include "shipper.h"

class ShipperContext : public Context
{
    Q_OBJECT
public:
    ShipperContext(Shipper* user, ServerBroker* broker, QObject *parent = nullptr);
    // make new order? put it in shipper class?
    //

private:
    Shipper* user;
};

#endif // SHIPPERCONTEXT_H
