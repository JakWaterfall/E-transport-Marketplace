#include "drivercontroller.h"

DriverController::DriverController(Driver user, ServerBroker* broker, ThreadSafeMap<QString, OrderContract *> *marketplace, QObject *parent)
    : Controller(broker, marketplace, parent), user(user)
{
    connect(broker, &ServerBroker::requestForOrderContracts, this, &DriverController::sendOrderContracts);
    connect(broker, &ServerBroker::requestForMarket, this, &DriverController::sendMarketContracts);
    connect(broker, &ServerBroker::acceptJob, this, &DriverController::acceptJobOffer);
    connect(broker, &ServerBroker::updateDeliveryState, this, &DriverController::updateDeliveryState);
}

void DriverController::sendOrderContracts()
{
    QMap<QString, OrderContract> orders;

    for(auto& ID : user.getOrderIDs())
    {
        if(marketplace->contains(ID))
        {
            marketplace->getMutex().lock();
            OrderContract contract = *marketplace->get(ID);
            marketplace->getMutex().unlock();
            orders[ID] = contract;
        }
        else
        {
            // delete ID from users list as it does not exist
            user.removeOrderID(ID);
        }
    }
    broker->sendUserRelatedOrderContracts(orders);
}

void DriverController::sendMarketContracts()
{
    QMap<QString, OrderContract> marketOrders;

    marketplace->getMutex().lock();
    for(auto it = marketplace->begin(); it != marketplace->end(); it++)
    {
        if(it.value()->getState() == OrderContract::State::inForwarderInventory)
        {
            // If the order is in the forwarders inventory then it is placed on the job board for drivers.
            marketOrders[it.key()] = *it.value();
        }
    }
    marketplace->getMutex().unlock();

    broker->sendMarketOrderContracts(marketOrders);
}

void DriverController::acceptJobOffer(const QString &orderID)
{
    if(marketplace->contains(orderID))
    {
        marketplace->getMutex().lock();
        OrderContract * contract = marketplace->get(orderID);

        if(contract->getState() == OrderContract::State::inForwarderInventory)
        {
            contract->setState(OrderContract::State::inDriverInventory);
            contract->setDriverEmail(user.getEmail());
            user.insertOrderID(orderID);
        }
        else
        {
            broker->sendErrorMessage("Job has been accept by another driver.");
        }
        marketplace->getMutex().unlock();
    }
    else
    {
        broker->sendErrorMessage("Order is no longer in the marketplace.");
    }
}

void DriverController::updateDeliveryState(const QString &orderID, const OrderContract::DeliveryState &deliveryState)
{
    if(marketplace->contains(orderID))
    {
        marketplace->getMutex().lock();
        OrderContract * contract = marketplace->get(orderID);
        contract->setDelveryState(deliveryState);
        marketplace->getMutex().unlock();
    }
    else
    {
        broker->sendErrorMessage("Order is no longer in the marketplace.");
    }
}
