#include "accountmanager.h"

AccountManager::AccountManager(QObject *parent) : QObject(parent)
{

}

bool AccountManager::verifyLogIn(QString email, QString password)
{
    database db;
    auto passwordInDatabase = db.getPassword(email);
    auto hashedInputtedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Algorithm::Sha512).toHex();

    return passwordInDatabase == hashedInputtedPassword;
}

bool AccountManager::emailExists(const QString &email)
{
    database db;
    return db.emailExists(email);
}

AccountManager::UserType AccountManager::getUserType(QString email) const
{
    database db;
    auto userType = db.getUserType(email);

    if(userType == "Shipper")
    {
        return UserType::ShipperUser;
    }
    else if(userType == "Forwarder")
    {
        return UserType::ForwarderUser;
    }
    else // Must be Driver
    {
        return UserType::DriverUser;
    }
}

Shipper AccountManager::createShipper(QString email)
{
    database db;
    auto userDetails = db.getUserDetails(email);

    return Shipper(userDetails[0], userDetails[1], userDetails[2], userDetails[3], orderCSVToVector(userDetails[4]));
}

Forwarder AccountManager::createForwarder(QString email)
{
    database db;
    auto userDetails = db.getUserDetails(email);

    return Forwarder(userDetails[0], userDetails[1], userDetails[2], userDetails[3], orderCSVToVector(userDetails[4]));
}

Driver AccountManager::createDriver(QString email)
{
    database db;
    auto userDetails = db.getUserDetails(email);

    return Driver(userDetails[0], userDetails[1], userDetails[2], userDetails[3], orderCSVToVector(userDetails[4]));
}

void AccountManager::createUser(const QString &name, const QString &email, const QString &password, const QString &address, const QString &postcode, const QString &userType)
{
    auto hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Algorithm::Sha512);

    database db;
    db.insertUserTable(name, email, hashedPassword.toHex(), address, postcode, userType);
}

QVector<QString> AccountManager::orderCSVToVector(QString &orderCSV)
{
    QVector<QString> orderIds;
    for(auto& id : orderCSV.split(","))
        orderIds.push_back(id);

    return orderIds;
}
