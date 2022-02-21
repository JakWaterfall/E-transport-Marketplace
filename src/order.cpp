#include "order.h"

Order::Order()
{}

Order::Order(QString description, QString source, QString destination, QString sourcePostcode, QString destinationPostcode, QString otherDetails,
             int width, int height, int depth, int weight, bool fragile, QDateTime _orderCreated)

    : sourceAddress(source), destinationAddress(destination), sourcePostcode(sourcePostcode), destinationPostcode(destinationPostcode), width(width),
      height(height), depth(depth), weight(weight), fragile(fragile), description(description), otherDetails(otherDetails), orderCreated(_orderCreated)
{}

const QString& Order::getSourceAddress() const
{
    return sourceAddress;
}

const QString& Order::getDestinationAddress() const
{
    return destinationAddress;
}

const QString &Order::getSourcePostcode() const
{
    return sourcePostcode;
}

const QString &Order::getDestinationPostcode() const
{
    return destinationPostcode;
}

const QString &Order::getDescription() const
{
    return description;
}

const QString &Order::getOtherDetails() const
{
    return otherDetails;
}

int Order::getWidth() const
{
    return width;
}

int Order::getHeight() const
{
    return height;
}

int Order::getDepth() const
{
    return depth;
}

int Order::getWeight() const
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
    stream >> sourceAddress >> destinationAddress >> sourcePostcode >> destinationPostcode >> width >> height >> depth >> weight >> fragile >> description >> otherDetails >> orderCreated;
    return stream;
}

QDataStream &Order::write(QDataStream &stream) const
{
    stream << sourceAddress << destinationAddress << sourcePostcode << destinationPostcode << width << height << depth << weight << fragile << description << otherDetails << orderCreated;
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
