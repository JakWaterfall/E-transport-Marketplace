#include "driver.h"

Driver::Driver(QString name, QString email, QString address, QString postcode, QVector<QString> orderIds)
    : User(name, email, address, postcode, orderIds)
{

}
