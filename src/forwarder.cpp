#include "forwarder.h"

Forwarder::Forwarder(QString name, QString email, QString address, QString postcode, QVector<QString> orderIds)
    : User(name, email, address, postcode, orderIds)
{

}

Forwarder::~Forwarder()
{

}

