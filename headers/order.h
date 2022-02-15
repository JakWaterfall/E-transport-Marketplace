#ifndef ORDER_H
#define ORDER_H

#include <QObject>
#include <QDateTime>

class Order : public QObject
{
    Q_OBJECT
public:
    Order(QString source, QString destination, QString dimensions, int weight, bool fragile,
          QString type, QDateTime _orderCreated = QDateTime::currentDateTimeUtc(), QObject *parent = nullptr);

public:
    const QString& getSourceAddress() const;
    const QString& getDestinationAddress() const;
    const QString& getDismensions() const;
    float getWeight() const;
    bool isFragile() const;
    const QString& getType() const;
    const QDateTime& getCreationDate() const;

signals:

private:
    QString sourceAddress;
    QString destinationAddress;
    QString dimensions;
    float weight;
    bool fragile;
    QString type;
    QDateTime orderCreated;
};

#endif // ORDER_H
