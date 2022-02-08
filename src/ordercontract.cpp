#include "ordercontract.h"

OrderContract::OrderContract(Order* order, QString sellerName, QString sellerEmail, QString responceTopic, QObject *parent)
    : QObject(parent), order(order), sellerName(sellerName), sellerEmail(sellerEmail), responceTopic(responceTopic)
{

}

OrderContract::~OrderContract()
{
    delete order;
}

const Order* OrderContract::getOrder() const
{
    return order;
}

const QString &OrderContract::getSellerName() const
{
    return sellerName;
}
const QString &OrderContract::getSellerEmail() const
{
    return sellerEmail;
}
const QString &OrderContract::getForwarderName() const
{
    return forwarderName;
}
const QString &OrderContract::getForwarderEmail() const
{
    return forwarderEmail;
}
double OrderContract::getForwarderBid() const
{
    return forwarderBid;
}
const QString &OrderContract::getResponceTopic() const
{
    return responceTopic;
}
void OrderContract::setForwarderName(const QString name)
{
    forwarderName = name;
}
void OrderContract::setForwarderEmail(const QString email)
{
    forwarderEmail = email;
}
void OrderContract::setForwarderBid(const double amount)
{
    forwarderBid = amount;
}
