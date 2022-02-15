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

Shipper *AccountManager::createShipper(QString email, QString password)
{
    return new Shipper("Jak", "J@email.com", "1234", "123 address lane");
}

Forwarder *AccountManager::createForwarder(QString email, QString password)
{
    return new Forwarder("Liam", "L@email.com", "1234", "321 address lane");
}
