#ifndef SERVERBROKER_H
#define SERVERBROKER_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

#include "messageparser.h"

class ServerBroker : public QObject
{
    Q_OBJECT
public:
    explicit ServerBroker(QTcpSocket* socket, QObject *parent = nullptr);
    void sendErrorMessage(QString message);
    void sendPageSignIn(const QString pageName) const;
    void sendOrderDetails(const QString &header, const QString& name, const QString& ID);

private:
    void sendMessage(QByteArray message) const;
    void processLogIn(QJsonDocument messageJSON);
    void processNewOrder(QJsonDocument orderContractJSON);


private slots:
    void processMessage();
    void socketDisconnected();

signals:
    void logInAttempt(QString email, QString password);
    void newOrderContract(OrderContract* orderContract);
    void disconnected();
    void requestForOrderDetails();

private:
    QTcpSocket* socket;
    MessageParser parser;
};

#endif // SERVERBROKER_H
