#include "accountmanager.h"
#include "database.h"

AccountManager::AccountManager(QObject *parent) : QObject(parent)
{

}

bool AccountManager::verifyLogIn(QString email, QString password)
{
    bool ok = false;
    database databaseController;
    if (databaseController.verifyLoginFromDatabase(email, password)){
        ok = true;
    }
    databaseController.~database();
    return ok;
}

AccountManager::UserType AccountManager::getUserType(QString email) const
{
    database databaseController;
    std::string thisUserType = databaseController.getUserTypeFromDatabase(email);
    if(thisUserType == "Shipper")
    {
        databaseController.~database();
        return UserType::ShipperUser;
    }
    else if(thisUserType == "Forwarder")
    {
        databaseController.~database();
        return UserType::ForwarderUser;
    }
    else
    {
        databaseController.~database();
        return UserType::DriverUser;
    }

}

Shipper AccountManager::createShipper(QString firstName, QString lastName, QString email, QString password, QString address)
{
    // INSERT INTO User(firstName, lastName, email, password, address, userType)
    database databaseController;
    databaseController.insertUserTable(firstName, lastName, email, password, address, "Shipper");
    databaseController.~database();
    return Shipper(firstName, email, password, address);
}

Forwarder AccountManager::createForwarder(QString firstName, QString lastName, QString email, QString password, QString address)
{
    database databaseController;
    databaseController.insertUserTable(firstName, lastName, email, password, address, "Forwarder");
    databaseController.~database();
    return Forwarder(firstName, email, password, address);
}

Driver AccountManager::createDriver(QString firstName, QString lastName, QString email, QString password, QString address)
{
    database databaseController;
    databaseController.insertUserTable(firstName, lastName, email, password, address, "Driver");
    databaseController.~database();
    return Driver(firstName, email, password, address);
}
