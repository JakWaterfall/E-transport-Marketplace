#include "accountmanager.h"

AccountManager::AccountManager(QObject *parent) : QObject(parent)
{

}

bool AccountManager::verifyLogIn(QString email, QString password)
{
    //STUB
    return true;
}

AccountManager::UserType AccountManager::getUserType(QString email) const
{
    // STUB
    if(email == "s")
    {
        return UserType::ShipperUser;
    }
    else
    {
        return UserType::ForwarderUser;
    }
}

Shipper *AccountManager::getShipper(QString email, QString password)
{
    return new Shipper("Jak", "Shipper", "J@email.com", "1234", "123 address lane");
}

Forwarder *AccountManager::getForwarder(QString email, QString password)
{
    return new Forwarder("Liam", "Forwarder", "L@email.com", "1234", "321 address lane");
}
