#ifndef FORWARDER_H
#define FORWARDER_H

#include "user.h"
#include "order.h"
#include "ordercontract.h"
#include <QObject>
#include <QMap>

class Forwarder : public User
{
public:
    Forwarder(QString name, QString email, QString password, QString address);
    ~Forwarder();
private:
};

#endif // FORWARDER_H
