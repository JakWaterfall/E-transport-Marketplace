#include "ordercontract.h"

OrderContract::OrderContract()
{

}

OrderContract::OrderContract(Order order, QString _ID, State state)
    : order(order), state(state)
{
    if (_ID == nullptr)
    {
        QDateTime now = QDateTime::currentDateTimeUtc();
        ID = now.toString();
    }
    else
    {
        ID = _ID;
    }
    // use UUID for id
}

OrderContract::~OrderContract()
{

}

const QString &OrderContract::getID() const
{
    return ID;
}

const Order &OrderContract::getOrder() const
{
    return order;
}

const QString &OrderContract::getShipperEmail() const
{
    return shipperEmail;
}

const QString &OrderContract::getForwarderEmail() const
{
    return forwarderEmail;
}

double OrderContract::getFinalBid() const
{
    return finalBid;
}

void OrderContract::setShipperEmail(const QString email)
{
    shipperEmail = email;
}

void OrderContract::setForwarderEmail(const QString email)
{
    forwarderEmail = email;
}

void OrderContract::setForwarderBid(const double amount)
{
    finalBid = amount;
}

void OrderContract::makeBid(const QString email, double amount)
{
    bids.push_back({email, amount});
}

QDataStream & operator<<(QDataStream &stream, const OrderContract &orderContract)
{
    return orderContract.write(stream);
}

QDataStream & operator>>(QDataStream &stream, OrderContract &orderContract)
{
    return orderContract.read(stream);
}

QDataStream &OrderContract::read(QDataStream &stream)
{
    stream >> ID >> order >> shipperEmail >> forwarderEmail >> driverEmail >> finalBid >> bids;
    qint32 state_int = 0;
    stream >> state_int;
    state = static_cast<State>(state_int);
    return stream;
}

QDataStream &OrderContract::write(QDataStream &stream) const
{
    stream << ID << order << shipperEmail << forwarderEmail << driverEmail << finalBid << bids << static_cast<qint32>(state);
    return stream;
}
