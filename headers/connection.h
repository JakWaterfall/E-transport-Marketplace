#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>

#include "ordercontract.h"
#include "shipper.h"
#include "forwarder.h"
#include "shippercontext.h"
#include "accountcontroller.h"
#include "serverbroker.h"

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QTcpSocket* socket, QMap<QString, OrderContract>* marketplace, QObject *parent = nullptr);
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
    QMap<QString, OrderContract>* marketplace;
    Context* context;
    AccountController* accountController;
};

#endif // CONNECTION_H
