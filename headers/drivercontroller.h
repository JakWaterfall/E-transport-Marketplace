#ifndef DRIVERCONTROLLER_H
#define DRIVERCONTROLLER_H

#include "controller.h"
#include "driver.h"

class DriverController : public Controller
{
    Q_OBJECT
public:
    DriverController(Driver user, ServerBroker* broker, ThreadSafeMap<QString, OrderContract *> *marketplace, QObject *parent = nullptr);

private slots:
    void sendOrderContracts();
    void sendMarketContracts();
    void acceptJobOffer(const QString& orderID);

private:
    Driver user;
};

#endif // DRIVERCONTROLLER_H
