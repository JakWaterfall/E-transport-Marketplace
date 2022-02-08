#include "forwarder.h"

Forwarder::Forwarder(QString firstName, QString lastName, QString email, QString password, QString address)
    : User(firstName, lastName, email, password, address)
{

}
// add these to user class instead if they are used
Forwarder::~Forwarder()
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

void Forwarder::addPendingOrder(OrderContract *contract)
{
    pendingOrders[contract->getOrder()->getID()] = contract;
}

const QMap<QString, OrderContract *> &Forwarder::getPendingOrders()
{
    return pendingOrders;
}
// //////////////////////////////////////////////////////////////////////
