#include "shippercontext.h"

ShipperContext::ShipperContext(Shipper* user, ServerBroker *broker, QObject *parent): Context(broker, parent), user(user)
{

}
