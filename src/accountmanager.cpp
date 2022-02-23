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
    else if(email == "f")
    {
        return UserType::ForwarderUser;
    }
    else
    {
        return UserType::DriverUser;
    }
}

Shipper AccountManager::createShipper(QString email, QString password)
{
    return Shipper("Jak", "Jak@email.com", "1234", "123 address lane");
}

Forwarder AccountManager::createForwarder(QString email, QString password)
{
    return Forwarder("Liam", "Liam@email.com", "1234", "321 address lane");
}

Driver AccountManager::createDriver(QString email, QString password)
{
    return Driver("Carl", "carlTheDriver@email.com", "pass1234", "214 watson street");
}
