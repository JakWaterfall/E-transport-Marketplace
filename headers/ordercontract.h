#ifndef ORDERCONTRACT_H
#define ORDERCONTRACT_H

#include <QObject>
#include <QVector>

#include "order.h"

class OrderContract : public QObject
{
    Q_OBJECT

public:
    enum class State {onMarket, inForwarderInventory, inDriverInventory};

    struct Bid
    {
        QString forwarderEmail;
        double amount;
    };

public:
    explicit OrderContract(Order* order, QString sellerEmail, QString _ID = nullptr, State state = State::onMarket, QObject *parent = nullptr);
    ~OrderContract();

    const QString& getID() const;
    const Order* getOrder() const;
    const QString& getSellerEmail() const;
    const QString& getForwarderEmail() const;
    double getFinalBid() const;
    const QString getState() const;

    void setForwarderEmail(const QString email);
    void setForwarderBid(const double amount);

signals:

private:
    QString ID;
    Order* order;
    QString sellerEmail;
    QString forwarderEmail;
    QString driverEmail;
    double finalBid;
    State state;

    QVector<Bid> bids;
    // make details a struct for seller, forwarder, consignee
};

#endif // ORDERCONTRACT_H
