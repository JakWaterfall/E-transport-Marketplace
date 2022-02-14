#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QMap>
#include <QTcpServer>
#include <QVector>
#include <QTcpSocket>
#include <algorithm>

#include "ordercontract.h"
#include "broker.h"
#include "connection.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

private slots:
    void newConnection();
    void removeConnection(Connection* connection);

signals:


private:
    QMap<QString, OrderContract> marketplace;
    //Broker broker;
    QTcpServer* tcpServer;
    QVector<Connection*> connections;
};

#endif // SERVER_H
