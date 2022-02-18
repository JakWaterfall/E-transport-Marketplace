#include "serverbroker.h"

ServerBroker::ServerBroker(QTcpSocket *socket, QObject *parent) : Broker(socket, parent)
{
    qDebug() << "ServerBroker created";
    connect(socket, &QTcpSocket::disconnected, this, &ServerBroker::socketDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &ServerBroker::processMessage);
}

void ServerBroker::sendErrorMessage(QString message)
{

}

void ServerBroker::sendMessage(QByteArray message) const
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

bool ServerBroker::processLogIn(QDataStream& inStream)
{
    QString email;
    QString password;
    inStream >> email >> password;

    if(!inStream.commitTransaction())
        return false;

    emit(logInAttempt(email, password));
    return true;
}

bool ServerBroker::processNewOrder(QDataStream &inStream)
{
    OrderContract * contract = new OrderContract();
    inStream >> *contract;

    if(!inStream.commitTransaction())
        return false;

    emit(newOrderContract(contract));
    return true;
}


bool ServerBroker::readBody(QDataStream &inStream)
{
    // Header only messages
    if(currentHeader == "getShipperOrderScreen")
    {
        emit(requestForOrderDetails());
        return true;
    }

    // Header and body messages
    inStream.startTransaction();
    if(currentHeader == "login")
    {
        return processLogIn(inStream);
    }
    else if (currentHeader == "register")
    {

    }
    else if (currentHeader == "newOrder")
    {
        return processNewOrder(inStream);
    }
}

void ServerBroker::sendOrderDetails(const QVector<OrderContract> orders)
{
    QString header = "shipperOrderContracts";
    if(socketReady())
    {
        QDataStream outStream(socket);
        outStream << header << orders;
    }
}

void ServerBroker::sendPageSignIn(const QString pageName) const
{
    QString header = "pageSignIn";
    if(socketReady())
    {
        QDataStream outStream(socket);
        outStream << header << pageName;
    }
}
