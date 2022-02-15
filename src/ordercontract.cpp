#include "ordercontract.h"

OrderContract::OrderContract(Order* order, QString sellerEmail, QString _ID, State state, QObject *parent)
    : QObject(parent), order(order), sellerEmail(sellerEmail), state(state)
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

const QString &OrderContract::getSellerEmail() const
{
    return sellerEmail;
}

const QString &OrderContract::getForwarderEmail() const
{
    return forwarderEmail;
}

double OrderContract::getFinalBid() const
{
    return finalBid;
}

void OrderContract::setForwarderEmail(const QString email)
{
    forwarderEmail = email;
}

void OrderContract::setForwarderBid(const double amount)
{
    finalBid = amount;
}
