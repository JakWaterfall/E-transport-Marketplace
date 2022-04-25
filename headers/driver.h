#ifndef DRIVER_H
#define DRIVER_H

#include "user.h"

class Driver : public User
{
public:
    Driver(QString name, QString email, QString address, QString postcode, QVector<QString> orderIds);
};

#endif // DRIVER_H
