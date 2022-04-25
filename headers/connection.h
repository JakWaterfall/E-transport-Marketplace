#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QThread>

#include "shippercontroller.h"
#include "forwardercontroller.h"
#include "drivercontroller.h"
#include "accountmanager.h"
#include "serverbroker.h"
#include "threadsafemap.h"

class Connection : public QThread
{
    Q_OBJECT
public:
    explicit Connection(QTcpSocket* socket, ThreadSafeMap<QString, OrderContract*>* marketplace, QObject *parent = nullptr);
    ~Connection();
    void run() override;

private:
    void changeSlotsAndSignalsToContext();

signals:
    void disconnected(Connection* connection);

private slots:
    void logIn(QString email, QString password);
    void registerAttempt(QString name, QString email, QString password, QString confirmPass, QString address, QString postcode, QString userType);
    void brokerDisconnected();

private:
    ServerBroker* broker;
    ThreadSafeMap<QString, OrderContract*>* marketplace;
    Controller* controller;
    AccountManager accountManager;
};

#endif // CONNECTION_H
