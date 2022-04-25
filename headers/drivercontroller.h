#ifndef DRIVERCONTROLLER_H
#define DRIVERCONTROLLER_H

#include "controller.h"
#include "driver.h"

class DriverController : public Controller
{
    Q_OBJECT
public:
    DriverController(Driver user, ServerBroker* broker, ThreadSafeMap<QString, OrderContract *> *marketplace, QObject *parent = nullptr);
    ~DriverController();

private slots:
    void sendOrderContracts();
    void sendMarketContracts();
    void acceptJobOffer(const QString& orderID);
    void updateDeliveryState(const QString& orderID, const OrderContract::DeliveryState &deliveryState);

private:
    Driver user;
};

#endif // DRIVERCONTROLLER_H
