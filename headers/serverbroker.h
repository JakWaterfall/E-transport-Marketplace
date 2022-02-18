#ifndef SERVERBROKER_H
#define SERVERBROKER_H

#include <QObject>
#include "broker.h"

class ServerBroker : public Broker
{
    Q_OBJECT
public:
    explicit ServerBroker(QTcpSocket* socket, QObject *parent = nullptr);
    void sendErrorMessage(QString message);
    void sendPageSignIn(const QString pageName) const;
    void sendOrderDetails(const QVector<OrderContract> orders);

private:
    void sendMessage(QByteArray message) const;
    bool processLogIn(QDataStream& inStream);
    bool processNewOrder(QDataStream& inStream);

    bool readBody(QDataStream& inStream) override;


private slots:

signals:
    void logInAttempt(QString email, QString password);
    void newOrderContract(OrderContract* orderContract);
    void requestForOrderDetails();

private:

};

#endif // SERVERBROKER_H
