#include "clientbroker.h"

ClientBroker::ClientBroker(QObject *parent) : QObject(parent)
{
    qDebug() << "ClientBroker created";
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress::LocalHost, 1234);
    // possibly waitForConnected here?

    connect(socket, &QTcpSocket::disconnected, this, &ClientBroker::socketDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &ClientBroker::processMessage);
}

void ClientBroker::logInAttempt(QString email, QString password)
{
    sendMessage(parser.logInAttemptToJSON(email, password));
}

void ClientBroker::sendMessage(QByteArray message)
{
    if (socket)
    {
        if (socket->isOpen())
        {
            QDataStream outStream(socket);
            outStream << message;
        }
        else
            qDebug() << "socket is not open";
    }
    else
        qDebug() << "socket is not connected";
}

void ClientBroker::processMessage()
{

}

void ClientBroker::socketDisconnected()
{
    emit(disconnected());
}
