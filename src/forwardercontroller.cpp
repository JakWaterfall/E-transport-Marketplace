#include "forwardercontroller.h"

ForwarderController::ForwarderController(Forwarder user, ServerBroker* broker, ThreadSafeMap<QString, OrderContract *> *marketplace, QObject *parent)
    : Controller(broker, marketplace, parent), user(user)
{
    connect(broker, &ServerBroker::requestForOrderContracts, this, &ForwarderController::sendOrderContracts);
    connect(broker, &ServerBroker::requestForMarket, this, &ForwarderController::sendMarketContracts);
    connect(broker, &ServerBroker::newBidOnOrder, this, &ForwarderController::addBidToOrder);
}

ForwarderController::~ForwarderController()
{
    saveOrderIdsToDatabase(user.getEmail(), user.getOrderIDs());
}

void ForwarderController::removeOtherForwardersBids(QMap<QString, OrderContract> &orders)
{
    for(auto& orderContract : orders)
    {
        orderContract.removeAllOtherBids(user.getEmail());
    }
}

void ForwarderController::sendOrderContracts()
{
    QMap<QString, OrderContract> orders;

    for(auto& ID : user.getOrderIDs())
    {
        if(marketplace->contains(ID))
        {
            marketplace->getMutex().lock();
            OrderContract contract = *marketplace->get(ID);
            marketplace->getMutex().unlock();

            if (contract.getState() != OrderContract::State::onMarket && contract.getForwarderEmail() != user.getEmail())
            {
                // If the order is no longer on the market (meaning it has a bid accepted) and the forwarders is not accosited with it.
                // the forwarder lost the bid. So we remove the order ID from the forwarder.
                user.removeOrderID(ID);
            }
            else
            {
                // If the order is still on the marketplace or the forwarders bid was accepted.
                orders[ID] = contract;
            }
        }
        else
        {
            // delete ID from users list as it does not exist
            user.removeOrderID(ID);
        }
    }
    removeOtherForwardersBids(orders);
    broker->sendUserRelatedOrderContracts(orders);
}

void ForwarderController::sendMarketContracts()
{
    QMap<QString, OrderContract> marketOrders;

    marketplace->getMutex().lock();
    for(auto it = marketplace->begin(); it != marketplace->end(); it++)
    {
        if(it.value()->getState() == OrderContract::State::onMarket && !it.value()->hasBidded(user.getEmail()))
        {
            // If the order is still on the market and the user hasnt already bidded on it.
            marketOrders[it.key()] = *it.value();
        }
    }
    marketplace->getMutex().unlock();

    broker->sendMarketOrderContracts(marketOrders);
}

void ForwarderController::addBidToOrder(const QString &orderID, OrderContract::Bid &bid)
{
    bid.forwarderEmail = user.getEmail(); // Add forwarders email to bid

    if(marketplace->contains(orderID))
    {
        marketplace->getMutex().lock();

        OrderContract* contract = marketplace->get(orderID);

        if(contract->getState() == OrderContract::State::onMarket) // only add bid if order is still on the market
        {
            contract->makeBid(bid);
            user.insertOrderID(orderID);
        }
        else
            broker->sendErrorMessage("Order is no longer on the marketplace");

        marketplace->getMutex().unlock();
        broker->sendMessage("Bid Sent!");
    }
    else
    {
        // Order no longer exists
        broker->sendErrorMessage("Order no longer exists.");
    }
}
