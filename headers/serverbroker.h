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

private:
    void processLogIn(QJsonDocument messageJSON);

private slots:
    void processMessage();
    void socketDisconnected();

signals:
    void logInAttempt(QString email, QString password);
    void disconnected();

private:
    QTcpSocket* socket;
    MessageParser parser;
};

#endif // SERVERBROKER_H
