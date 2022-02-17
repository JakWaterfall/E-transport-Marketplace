#ifndef CLIENTBROKER_H
#define CLIENTBROKER_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>

#include "messageparser.h"

class ClientBroker : public QObject
{
    Q_OBJECT
public:
    explicit ClientBroker(QObject *parent = nullptr);

    void logInAttempt(QString email, QString password);
    void sendOrderToMarketplace(const OrderContract *orderContract);
    void buildOrderScreen();

private:
    void sendMessage(QByteArray message);
    void processPageSignIn(QJsonDocument pageSignInJSON);
    void processPendingOrders(QJsonDocument pendingOrdersJSON);

private slots:
    void processMessage();
    void socketDisconnected();

signals:
    void logInAsShipper();
    void logInAsForwarder();
    void logInAsDriver();
    void disconnected();
    void signInToPage(QString pageName);
    void pendingOrder(const QString& name, const QString& ID);

private:
    QTcpSocket* socket;
    MessageParser parser;

};

#endif // CLIENTBROKER_H
