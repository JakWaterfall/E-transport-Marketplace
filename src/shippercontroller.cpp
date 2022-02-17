#include "shippercontroller.h"

ShipperController::ShipperController(Shipper* user, ServerBroker *broker, ThreadSafeMap<QString, OrderContract *> *marketplace, QObject *parent)
    : Controller(broker, marketplace, parent), user(user)
{
    qDebug() << "Shipper controller created";
    // send user details and order ids they hold?
    connect(broker, &ServerBroker::newOrderContract, this, &ShipperController::makeNewOrder);
    connect(broker, &ServerBroker::requestForOrderDetails, this, &ShipperController::sendOrderDetails);
}

ShipperController::~ShipperController()
{

}

void ShipperController::makeNewOrder(OrderContract *orderContract)
{
    QString ID = orderContract->getID();
    orderContract->setShipperEmail(user->getEmail());

    user->insertOrderID(ID);
    marketplace->insert(ID, orderContract);
    qDebug() << "new order made";
    qDebug() << "marketplace size:" << marketplace->size();

    marketplace->getMutex().lock();
    for(auto it = marketplace->begin(); it != marketplace->end(); it++)
    {
        qDebug() << it.key();
    }
    marketplace->getMutex().unlock();
}

void ShipperController::sendOrderDetails()
{
    for(auto& ID : user->getOrderIDs())
    {
        if(marketplace->contains(ID))
        {
            marketplace->getMutex().lock();
            broker->sendOrderDetails("pendingOrders", marketplace->get(ID)->getShipperEmail(), ID);
            marketplace->getMutex().unlock();
        }
        else
        {
            // delete ID from users list as it does not exist?
        }
    }
}
