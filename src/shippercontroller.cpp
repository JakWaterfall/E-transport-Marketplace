#include "shippercontroller.h"

ShipperController::ShipperController(Shipper user, ServerBroker *broker, ThreadSafeMap<QString, OrderContract *> *marketplace, QObject *parent)
    : Controller(broker, marketplace, parent), user(user)
{
    qDebug() << "Shipper controller created";
    // send user details and order ids they hold?
    connect(broker, &ServerBroker::newOrderContract, this, &ShipperController::makeNewOrder);
    connect(broker, &ServerBroker::requestForOrderContracts, this, &ShipperController::sendOrderContracts);
    connect(broker, &ServerBroker::acceptBid, this, &ShipperController::acceptBidOnOrder);
}

ShipperController::~ShipperController()
{

}

void ShipperController::makeNewOrder(OrderContract *orderContract)
{
    QString ID = orderContract->getID();
    orderContract->setShipperEmail(user.getEmail());

    user.insertOrderID(ID);
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

void ShipperController::sendOrderContracts()
{
    QMap<QString, OrderContract> orders;
    for(auto& ID : user.getOrderIDs())
    {
        if(marketplace->contains(ID))
        {
            marketplace->getMutex().lock();
            orders[ID] = *marketplace->get(ID); // change this becasue its not thread safe. maybe make the marketplace hold non pointers to orders.
            marketplace->getMutex().unlock();
        }
        else
        {
            user.removeOrderID(ID);
            // delete ID from users list as it does not exist?
        }
    }
    broker->sendUserRelatedOrderContracts(orders);
}

void ShipperController::acceptBidOnOrder(const QString &orderID, OrderContract::Bid &bid)
{
    if(marketplace->contains(orderID))
    {
        marketplace->getMutex().lock();

        OrderContract* contract = marketplace->get(orderID);

        contract->setFinalBid(bid.amount);
        contract->setForwarderEmail(bid.forwarderEmail);
        contract->setFinalDriverPrice(bid.driverPrice);
        contract->clearBids();
        contract->setState(OrderContract::State::inForwarderInventory);

        marketplace->getMutex().unlock();
    }
    else
    {
        // Order no longer exists
        broker->sendErrorMessage("Order no longer exists.");
    }
}
