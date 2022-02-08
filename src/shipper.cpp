#include "shipper.h"

Shipper::Shipper(QString firstName, QString lastName, QString email, QString password, QString address)
    : User(firstName, lastName, email, password, address)
{

}

Shipper::~Shipper()
{
    // clean up all orders and objects
    for(auto& order : pendingOrders)
    {
        delete order;
    }
    for(auto& order : compleatedOrders)
    {
        delete order;
    }
}

void Shipper::addPendingOrder(OrderContract *contract)
{
    pendingOrders[contract->getOrder()->getID()] = contract;
}

const QMap<QString, OrderContract *> &Shipper::getPendingOrders()
{
    return pendingOrders;
}
