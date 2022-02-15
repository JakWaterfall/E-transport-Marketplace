#include "shippercontroller.h"

ShipperController::ShipperController(Shipper* user, ServerBroker *broker, QObject *parent): Controller(broker, parent), user(user)
{
    // send msg to client allowing them into shipper page
    // send user details and order ids they hold?
}
