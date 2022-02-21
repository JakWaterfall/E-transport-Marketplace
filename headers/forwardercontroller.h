#ifndef FORWARDERCONTROLLER_H
#define FORWARDERCONTROLLER_H

#include <controller.h>
#include <forwarder.h>

class ForwarderController : public Controller
{
    Q_OBJECT
public:
    ForwarderController(Forwarder user, ServerBroker* broker, ThreadSafeMap<QString, OrderContract *> *marketplace, QObject *parent = nullptr);

private:
    void removeOtherForwardersBids(QMap<QString, OrderContract>& orders);

private slots:
    void sendOrderContracts();
    void sendMarketContracts();
    void addBidToOrder(const QString& orderID, OrderContract::Bid& bid);

private:
    Forwarder user;
};

#endif // FORWARDERCONTROLLER_H
