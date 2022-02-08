#include "order.h"

Order::Order(QString source, QString destination, QString dimensions, int weight, bool fragile, QString type, QDateTime _orderCreated, QString _ID, QObject *parent):
    QObject(parent), sourceAddress(source), destinationAddress(destination), dimensions(dimensions), weight(weight), fragile(fragile), type(type), orderCreated(_orderCreated)
{
    if (_ID == nullptr)
    {
        QDateTime now = QDateTime::currentDateTimeUtc();
        ID = now.toString();
    }
    else
    {
        ID = _ID;
    }
    // use UUID for id
}

const QString& Order::getID() const
{
    return ID;
}

const QString& Order::getType() const
{
    return type;
}

const QString& Order::getSourceAddress() const
{
    return sourceAddress;
}
const QString& Order::getDestinationAddress() const
{
    return destinationAddress;
}
const QString& Order::getDismensions() const
{
    return dimensions;
}
float Order::getWeight() const
{
    return weight;
}
bool Order::isFragile() const
{
    return fragile;
}
const QString& Order::getCurrentLocation() const
{
    return CurrentLocation;
}
const QDateTime& Order::getCreationDate() const
{
    return orderCreated;
}
