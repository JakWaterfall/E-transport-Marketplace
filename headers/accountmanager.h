#ifndef ACCOUNTCONTROLLER_H
#define ACCOUNTCONTROLLER_H

#include <QObject>
#include <QCryptographicHash>
#include <shipper.h>
#include <forwarder.h>
#include <driver.h>
#include <database.h>

class AccountManager : public QObject
{
    Q_OBJECT

public:
    enum UserType {ShipperUser, ForwarderUser, DriverUser};

public:
    explicit AccountManager(QObject *parent = nullptr);
    bool verifyLogIn(QString email, QString password);
    bool emailExists(const QString& email);
    UserType getUserType(QString email) const;
    Shipper createShipper(QString email);
    Forwarder createForwarder(QString email);
    Driver createDriver(QString email);
    void createUser(const QString& name, const QString& email, const QString& password, const QString& address, const QString& postcode, const QString& userType);
signals:

private:
    QVector<QString> orderCSVToVector(QString& orderCSV);

};

#endif // ACCOUNTCONTROLLER_H
