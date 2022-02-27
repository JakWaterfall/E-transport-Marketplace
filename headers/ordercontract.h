#ifndef ORDERCONTRACT_H
#define ORDERCONTRACT_H

#include <QVector>
#include <QUuid>
#include <QDebug>

#include "order.h"

class OrderContract
{

public:
    enum class State {onMarket, inForwarderInventory, inDriverInventory};
    enum class DeliveryState {notApplicable, inTransit, atDepot, outForDelivery, failedToDeliver, successfullyDelivered};
    const static QMap<State, QString> stateToString;
    const static QMap<DeliveryState, QString> DeliveryStateToString;

    struct Bid
    {
        QString optionalExtras;
        double amount;
        double driverPrice;
        QString forwarderEmail;

        friend QDataStream &operator<< (QDataStream& stream, const Bid &bid)
        {
            return stream << bid.forwarderEmail << bid.amount << bid.optionalExtras << bid.driverPrice;
        }
        friend QDataStream &operator>> (QDataStream& stream, Bid &bid)
        {
            return stream >> bid.forwarderEmail >> bid.amount >> bid.optionalExtras >> bid.driverPrice;
        }
    };

public:
    OrderContract();
    explicit OrderContract(Order order, QString consigneeName, QString consigneeNumber, QString _ID = nullptr,
                           State state = State::onMarket, DeliveryState deliveryState = DeliveryState::notApplicable);
    ~OrderContract();

    const QString& getID() const;
    const Order& getOrder() const;
    const QString& getShipperEmail() const;
    const QString& getForwarderEmail() const;
    const QString& getDriverEmail() const;
    const QString& getConsigneeName() const;
    const QString& getConsigneeNumber() const;
    double getFinalBid() const;
    double getFinalDriverPrice() const;
    State getState() const;
    DeliveryState getDeliveryState() const;
    const QVector<Bid> getBids() const;

    void setShipperEmail(const QString email);
    void setForwarderEmail(const QString email);
    void setDriverEmail(const QString email);
    void setFinalBid(const double amount);
    void setFinalDriverPrice(const double amount);
    void makeBid(Bid bid);
    void setState(State _state);
    void setDelveryState(DeliveryState state);

    void clearBids();
    bool hasBidded(const QString& email);
    void removeAllOtherBids(const QString& email);

    friend QDataStream &operator<< (QDataStream& stream, const OrderContract &orderContract);
    friend QDataStream &operator>> (QDataStream& stream, OrderContract &orderContract);
    QDataStream & read(QDataStream & stream);
    QDataStream & write(QDataStream & stream) const;

    friend QDataStream &operator<< (QDataStream& stream, const OrderContract::DeliveryState & state);
    friend QDataStream &operator>> (QDataStream& stream, OrderContract::DeliveryState & state);

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
    QString consigneeName;
    QString consigneeNumber;
    double finalBid;
    double finalDriverPrice;
    State state;
    DeliveryState deliveryState;
    QVector<Bid> bids;
};

#endif // ORDERCONTRACT_H
