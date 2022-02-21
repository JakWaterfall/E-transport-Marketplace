#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include "shippercontroller.h"
#include "forwardercontroller.h"
#include "accountmanager.h"
#include "serverbroker.h"
#include "threadsafemap.h"

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QTcpSocket* socket, ThreadSafeMap<QString, OrderContract*>* marketplace, QObject *parent = nullptr);
    ~Connection();

private:
    void changeSlotsAndSignalsToContext();

signals:
    void disconnected(Connection* connection);

private slots:
    void logIn(QString email, QString password);
    void brokerDisconnected();

private:
    ServerBroker* broker;
    ThreadSafeMap<QString, OrderContract*>* marketplace;
    Controller* controller;
    AccountManager accountManager;
};

#endif // CONNECTION_H
