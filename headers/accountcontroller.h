#ifndef ACCOUNTCONTROLLER_H
#define ACCOUNTCONTROLLER_H

#include <QObject>
#include <shipper.h>
#include <forwarder.h>

class AccountController : public QObject
{
    Q_OBJECT

public:
    enum UserType {ShipperUser, ForwarderUser, DriverUser};

public:
    explicit AccountController(QObject *parent = nullptr);
    bool verifyLogIn(QString email, QString password);
    UserType getUserType(QString email) const;
    Shipper* getShipper(QString email, QString password);
    Forwarder*  getForwarder(QString email, QString password);
    const QString getError();
signals:

private:
    UserType type;
    Shipper* shipper;
    Forwarder* forwarder;

};

#endif // ACCOUNTCONTROLLER_H
