#ifndef SHIPPER_H
#define SHIPPER_H

#include "user.h"
#include "order.h"
#include "ordercontract.h"
#include <QObject>
#include <QMap>

class Shipper : public User
{
public:
    Shipper(QString name, QString email, QString password, QString address);
    ~Shipper();

private:

};

#endif // SHIPPER_H
