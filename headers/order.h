#ifndef ORDER_H
#define ORDER_H

#include <QObject>
#include <QDateTime>

class Order : public QObject
{
    Q_OBJECT
public:
    Order(QString source, QString destination, QString dimensions, int weight, bool fragile,
          QString type, QDateTime _orderCreated = QDateTime::currentDateTimeUtc(), QString _ID = nullptr, QObject *parent = nullptr);
    // maybe change user to something more concreate.
    // should the order come with user details? or maybe a container which wraps the order has them that has the user responce topic.
public:
    const QString& getID() const;
    const QString& getSourceAddress() const;
    const QString& getDestinationAddress() const;
    const QString& getDismensions() const;
    float getWeight() const;
    bool isFragile() const;
    const QString& getType() const;
    const QString& getCurrentLocation() const;
    const QDateTime& getCreationDate() const;

signals:

private:
    QString ID;
    QString sourceAddress;
    QString destinationAddress;
    QString dimensions;
    float weight;
    bool fragile;
    QString type;
    QString CurrentLocation;
    QDateTime orderCreated;
};

#endif // ORDER_H
