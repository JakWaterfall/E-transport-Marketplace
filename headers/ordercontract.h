#ifndef ORDERCONTRACT_H
#define ORDERCONTRACT_H

#include <QVector>
#include <QDebug>

#include "order.h"

class OrderContract
{

public:
    enum class State {onMarket, inForwarderInventory, inDriverInventory};

    struct Bid
    {
        QString forwarderEmail;
        double amount;
        friend QDataStream &operator<< (QDataStream& stream, const Bid &bid)
        {
            return stream << bid.forwarderEmail << bid.amount;
        }
        friend QDataStream &operator>> (QDataStream& stream, Bid &bid)
        {
            return stream >> bid.forwarderEmail >> bid.amount;
        }
    };

public:
    OrderContract();
    explicit OrderContract(Order order, QString _ID = nullptr, State state = State::onMarket);
    ~OrderContract();

    const QString& getID() const;
    const Order& getOrder() const;
    const QString& getShipperEmail() const;
    const QString& getForwarderEmail() const;
    double getFinalBid() const;
    const QString getState() const;

    void setShipperEmail(const QString email);
    void setForwarderEmail(const QString email);
    void setForwarderBid(const double amount);
    void makeBid(const QString email, double amount);

    friend QDataStream &operator<< (QDataStream& stream, const OrderContract &orderContract);
    friend QDataStream &operator>> (QDataStream& stream, OrderContract &orderContract);
    QDataStream & read(QDataStream & stream);
    QDataStream & write(QDataStream & stream) const;

    friend QDebug operator<<(QDebug debug, const OrderContract& contract)
    {
        debug << contract.getID() << contract.getOrder();
        return debug;
    }

private:
    QString ID;
    Order order;
    QString shipperEmail;
    QString forwarderEmail;
    QString driverEmail;
    double finalBid;
    State state;

    QVector<Bid> bids;
    // make details a struct for seller, forwarder, consignee
};

#endif // ORDERCONTRACT_H
