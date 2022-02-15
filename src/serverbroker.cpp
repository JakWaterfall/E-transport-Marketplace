#include "serverbroker.h"

ServerBroker::ServerBroker(QTcpSocket *socket, QObject *parent) : QObject(parent), socket(socket)
{
    qDebug() << "ServerBroker created";
    connect(socket, &QTcpSocket::disconnected, this, &ServerBroker::socketDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &ServerBroker::processMessage);
}

void ServerBroker::sendErrorMessage(QString message)
{

}

void ServerBroker::processLogIn(QJsonDocument messageJSON)
{
    qDebug() << "processing log in";
    QString email = messageJSON["email"].toString();
    QString password = messageJSON["password"].toString();
    emit(logInAttempt(email, password));
}

void ServerBroker::processMessage()
{
//    QString hello = socket->readAll();
//    qDebug() << hello;
//    qDebug() << hello.size();

    qDebug() << "processing message";

    QDataStream inStream(socket);
    inStream.startTransaction();

    QByteArray message;
    inStream >> message;

    if (!inStream.commitTransaction())
    {
        qDebug() << "waiting for more data";
        return;
    }

    QJsonDocument messageJSON = parser.toJSONdocument(message);
    QString header = messageJSON["header"].toString();

    if(header == "login")
    {
        processLogIn(messageJSON);
    }
    else if (header == "register")
    {

    }
    else
    {

    }
}

void ServerBroker::socketDisconnected()
{
    emit(disconnected());
}
