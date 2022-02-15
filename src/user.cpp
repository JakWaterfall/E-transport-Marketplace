#include "user.h"

User::User(QString name, QString email, QString password, QString address)
    : name(name), email(email), password(password), address(address)
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

const QString &User::getPassword()
{
    return password;
}

const QString &User::getAddress()
{
    return address;
}

const QVector<QString> User::getOrderIDs()
{
    return ordersIDs;
}

void User::insertOrderID(QString ID)
{
    ordersIDs.push_back(ID);
}
