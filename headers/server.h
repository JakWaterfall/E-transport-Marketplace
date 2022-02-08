#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QMap>

#include "ordercontract.h"
#include "broker.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

signals:


private:
    QMap<QString, OrderContract> marketplace;
    Broker broker;
};

#endif // SERVER_H
