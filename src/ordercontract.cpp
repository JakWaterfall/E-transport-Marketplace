#include "ordercontract.h"

OrderContract::OrderContract(Order* order, QString _ID, State state, QObject *parent)
    : QObject(parent), order(order), state(state)
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
    delete order;
}

const QString &OrderContract::getID() const
{
    return ID;
}

const Order* OrderContract::getOrder() const
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
