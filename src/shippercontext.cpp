#include "shippercontext.h"

ShipperContext::ShipperContext(Shipper* user, ServerBroker *broker, QObject *parent): Context(broker, parent), user(user)
{
    // send msg to client allowing them into shipper page
    // send user details and order ids they hold?
}
