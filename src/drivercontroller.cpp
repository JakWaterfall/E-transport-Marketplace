#include "drivercontroller.h"

DriverController::DriverController(Driver user, ServerBroker* broker, ThreadSafeMap<QString, OrderContract *> *marketplace, QObject *parent)
    : Controller(broker, marketplace, parent), user(user)
{
    connect(broker, &ServerBroker::requestForOrderContracts, this, &DriverController::sendOrderContracts);
    connect(broker, &ServerBroker::requestForMarket, this, &DriverController::sendMarketContracts);
    connect(broker, &ServerBroker::acceptJob, this, &DriverController::acceptJobOffer);
}

void DriverController::sendOrderContracts()
{

}

void DriverController::sendMarketContracts()
{

}

void DriverController::acceptJobOffer(const QString &orderID)
{

}
