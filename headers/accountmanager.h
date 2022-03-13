#ifndef ACCOUNTCONTROLLER_H
#define ACCOUNTCONTROLLER_H

#include <QObject>
#include <shipper.h>
#include <forwarder.h>
#include <driver.h>

class AccountManager : public QObject
{
    Q_OBJECT

public:
    enum UserType {ShipperUser, ForwarderUser, DriverUser};

public:
    explicit AccountManager(QObject *parent = nullptr);
    bool verifyLogIn(QString email, QString password);
    UserType getUserType(QString email) const;
    Shipper createShipper(QString email, QString password);
    Forwarder createForwarder(QString firstName, QString lastName, QString email, QString password, QString address);
    Driver createDriver(QString firstName, QString lastName, QString email, QString password, QString address);
    const QString getError();
signals:

private:


};

#endif // ACCOUNTCONTROLLER_H
