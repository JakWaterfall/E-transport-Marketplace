#include "order.h"

Order::Order()
{

}

Order::Order(QString source, QString destination, QString dimensions, int weight, bool fragile, QString type, QDateTime _orderCreated)
    : sourceAddress(source), destinationAddress(destination), dimensions(dimensions), weight(weight), fragile(fragile), type(type), orderCreated(_orderCreated)
{

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

const QDateTime& Order::getCreationDate() const
{
    return orderCreated;
}

QDataStream &Order::read(QDataStream &stream)
{
    stream >> sourceAddress >> destinationAddress >> dimensions >> weight >> fragile >> type >> orderCreated;
    return stream;
}

QDataStream &Order::write(QDataStream &stream) const
{
    stream << sourceAddress << destinationAddress << dimensions << weight << fragile << type << orderCreated;
    return stream;
}

QDataStream& operator<<(QDataStream &stream, const Order &order)
{
    return order.write(stream);
}

QDataStream& operator>>(QDataStream &stream, Order &order)
{
    return order.read(stream);
}
