#ifndef ORDER_H
#define ORDER_H

#include <QDateTime>
#include <QDataStream>
#include <QDebug>

class Order
{

public:
    Order();
    Order(QString source, QString destination, QString dimensions, int weight, bool fragile,
          QString type, QDateTime _orderCreated = QDateTime::currentDateTimeUtc());

public:
    const QString& getSourceAddress() const;
    const QString& getDestinationAddress() const;
    const QString& getDismensions() const;
    float getWeight() const;
    bool isFragile() const;
    const QString& getType() const;
    const QDateTime& getCreationDate() const;

    friend QDataStream &operator<< (QDataStream& stream, const Order &order);
    friend QDataStream &operator>> (QDataStream& stream, Order &order);
    QDataStream & read(QDataStream & stream);
    QDataStream & write(QDataStream & stream) const;

    friend QDebug operator<<(QDebug debug, const Order& order)
    {
        debug << order.getType() << order.getCreationDate();
        return debug;
    }


private:
    QString sourceAddress;
    QString destinationAddress;
    QString dimensions;
    int weight;
    bool fragile;
    QString type;
    QDateTime orderCreated;
};

#endif // ORDER_H
