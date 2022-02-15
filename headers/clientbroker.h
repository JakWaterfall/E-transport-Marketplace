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

private:
    void sendMessage(QByteArray message);

private slots:
    void processMessage();
    void socketDisconnected();

signals:
    void logInAsShipper();
    void logInAsForwarder();
    void logInAsDriver();
    void disconnected();

private:
    QTcpSocket* socket;
    MessageParser parser;

};

#endif // CLIENTBROKER_H
