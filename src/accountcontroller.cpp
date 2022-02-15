#include "accountcontroller.h"

AccountController::AccountController(QObject *parent) : QObject(parent)
{

}

bool AccountController::verifyLogIn(QString email, QString password)
{
    //STUB
    return true;
}

AccountController::UserType AccountController::getUserType(QString email) const
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

Shipper *AccountController::getShipper(QString email, QString password)
{
    return new Shipper("Jak", "Shipper", "J@email.com", "1234", "123 address lane");
}

Forwarder *AccountController::getForwarder(QString email, QString password)
{
    return new Forwarder("Liam", "Forwarder", "L@email.com", "1234", "321 address lane");
}
