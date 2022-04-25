#include "user.h"

User::User(QString name, QString email, QString address, QString postcode, QVector<QString> ordersIDs)
    : name(name), email(email), address(address), postcode(postcode), ordersIDs(ordersIDs)
{

}

User::~User()
{

}

const QString &User::getName()
{
    return name;
}

const QString &User::getEmail()
{
    return email;
}

const QString &User::getAddress()
{
    return address;
}

const QString &User::getPostcode()
{
    return postcode;
}

const QVector<QString> User::getOrderIDs()
{
    return ordersIDs;
}

void User::insertOrderID(QString ID)
{
    ordersIDs.push_back(ID);
}

void User::removeOrderID(const QString &ID)
{
    ordersIDs.erase(std::remove(std::begin(ordersIDs), std::end(ordersIDs), ID), std::end(ordersIDs));
}
