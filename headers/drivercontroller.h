#ifndef DRIVERCONTROLLER_H
#define DRIVERCONTROLLER_H

#include "controller.h"
#include "driver.h"

/**
 * @brief The DriverController class holds all the logic for the Driver.
 */
class DriverController : public Controller
{
    Q_OBJECT
public:
    /**
     * @brief DriverController constructor.
     * @param user the user of the system.
     * @param broker The Message broker for the server.
     * @param marketplace The marketplace of orders.
     * @param parent The parent object for QT Framework.
     */
    DriverController(Driver user, ServerBroker* broker, ThreadSafeMap<QString, OrderContract *> *marketplace, QObject *parent = nullptr);
    ~DriverController();

private slots:
    /**
     * @brief Sends the order contracts associated with the driver user to the client via the broker.
     */
    void sendOrderContracts();

    /**
     * @brief Sends all the order contacts that are currently in a forwarders inventory. This will be a list of potential orders that the user may want to accept a job offer on.
     */
    void sendMarketContracts();

    /**
     * @brief Accepts a job offer.
     * @param orderID The orders ID that the driver wishes to accept.
     */
    void acceptJobOffer(const QString& orderID);

    /**
     * @brief Updates the Delivery state of an order.
     * @param orderID The order ID to be updated.
     * @param deliveryState The new delivery state to be added.
     */
    void updateDeliveryState(const QString& orderID, const OrderContract::DeliveryState &deliveryState);

private:
    Driver user;
};

#endif // DRIVERCONTROLLER_H
