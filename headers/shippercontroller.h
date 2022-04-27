#ifndef SHIPPERCONTEXT_H
#define SHIPPERCONTEXT_H

#include "controller.h"
#include "shipper.h"

/**
 * @brief The ShipperController class holds all the logic for the Shipper.
 */
class ShipperController : public Controller
{
    Q_OBJECT
public:
    /**
     * @brief ShipperController constructor.
     * @param user The user of the system.
     * @param broker The Message broker for the server.
     * @param marketplace The marketplace of orders.
     * @param parent The parent object for QT Framework.
     */
    ShipperController(Shipper user, ServerBroker* broker, ThreadSafeMap<QString, OrderContract *> *marketplace, QObject *parent = nullptr);
    ~ShipperController();

private slots:
    /**
     * @brief Places a new order contract into the marketplace.
     * @param orderContract The order to be placed.
     */
    void makeNewOrder(OrderContract * orderContract);

    /**
     * @brief Sends the order contracts associated with the user to the client via the broker.
     */
    void sendOrderContracts();

    /**
     * @brief Accepts a bid made by a forwarder on the shippers order.
     * @param orderID The Id of the order.
     * @param bid The bid to be accepted.
     */
    void acceptBidOnOrder(const QString& orderID, OrderContract::Bid& bid);

private:
    Shipper user;
};

#endif // SHIPPERCONTEXT_H
