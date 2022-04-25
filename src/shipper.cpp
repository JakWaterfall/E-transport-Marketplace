#include "shipper.h"

Shipper::Shipper(QString name, QString email, QString address, QString postcode, QVector<QString> orderIds)
    : User(name, email, address, postcode, orderIds)
{

}

Shipper::~Shipper()
{

}
