#ifndef FORWARDERCONTROLLER_H
#define FORWARDERCONTROLLER_H

#include "controller.h"
#include "forwarder.h"

/**
 * @brief The ForwarderController class holds all the logic for the Forwarder.
 */
class ForwarderController : public Controller
{
    Q_OBJECT
public:
    /**
     * @brief ForwarderController constructor.
     * @param user the user of the system.
     * @param broker The Message broker for the server.
     * @param marketplace The marketplace of orders.
     * @param parent The parent object for QT Framework.
     */
    ForwarderController(Forwarder user, ServerBroker* broker, ThreadSafeMap<QString, OrderContract *> *marketplace, QObject *parent = nullptr);
    ~ForwarderController();

private:
    /**
     * @brief Removes all other bids from order except the current forwarder user. This is so when I send the order to the forwarder client, other bids are not visable.
     * @param orders The orders to be stripped of bids.
     */
    void removeOtherForwardersBids(QMap<QString, OrderContract>& orders);

private slots:
    /**
     * @brief Sends the order contracts associated with the user to the client via the broker.
     */
    void sendOrderContracts();

    /**
     * @brief Sends all the order contacts that are currently on the market that the user has not already bidded on to the client. This will be a list of potential orders that the user may want to bid on.
     */
    void sendMarketContracts();

    /**
     * @brief Adds a bid on an order.
     * @param orderID The ID of the order to be bidded on.
     * @param bid The bid to be added to a order.
     */
    void addBidToOrder(const QString& orderID, OrderContract::Bid& bid);

private:
    Forwarder user;
};

#endif // FORWARDERCONTROLLER_H
