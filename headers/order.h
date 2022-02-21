#ifndef ORDER_H
#define ORDER_H

#include <QDateTime>
#include <QDataStream>
#include <QDebug>

class Order
{

public:
    Order();
    Order(QString description, QString source, QString destination, QString sourcePostcode, QString destinationPostcode, QString otherDetails,
          int width, int height, int depth, int weight, bool fragile, QDateTime _orderCreated = QDateTime::currentDateTimeUtc());

public:
    const QString& getSourceAddress() const;
    const QString& getDestinationAddress() const;
    const QString& getSourcePostcode() const;
    const QString& getDestinationPostcode() const;

    const QString& getDescription() const;
    const QString& getOtherDetails() const;
    int getWidth() const;
    int getHeight() const;
    int getDepth() const;
    int getWeight() const;
    bool isFragile() const;
    const QDateTime& getCreationDate() const;

    friend QDataStream &operator<< (QDataStream& stream, const Order &order);
    friend QDataStream &operator>> (QDataStream& stream, Order &order);
    QDataStream & read(QDataStream & stream);
    QDataStream & write(QDataStream & stream) const;

    friend QDebug operator<<(QDebug debug, const Order& order)
    {
        debug << order.getDescription() << order.getCreationDate();
        return debug;
    }


private:
    QString sourceAddress;
    QString destinationAddress;
    QString sourcePostcode;
    QString destinationPostcode;
    int width;
    int height;
    int depth;
    int weight;
    bool fragile;
    QString description;
    QString otherDetails;
    QDateTime orderCreated;
};

#endif // ORDER_H
