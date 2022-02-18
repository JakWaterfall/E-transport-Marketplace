#include "clientbroker.h"

ClientBroker::ClientBroker(QObject *parent) : Broker(new QTcpSocket(), parent)
{
    qDebug() << "ClientBroker created";
    socket->connectToHost(QHostAddress::LocalHost, 1234);
    // possibly waitForConnected here?

    connect(socket, &QTcpSocket::disconnected, this, &ClientBroker::socketDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &ClientBroker::processMessage);
}

void ClientBroker::logInAttempt(QString email, QString password)
{
    QString header = "login";
    if(socketReady())
    {
        QDataStream outStream(socket);
        outStream << header << email << password;
    }
}

void ClientBroker::sendOrderToMarketplace(const OrderContract *orderContract)
{
    QString header = "newOrder";
    if(socketReady())
    {
        QDataStream outStream(socket);
        outStream << header << *orderContract;
    }
}

void ClientBroker::buildOrderScreen()
{
    QString header = "getShipperOrderScreen";
    if(socketReady())
    {
        QDataStream outStream(socket);
        outStream << header;
    }
}

bool ClientBroker::readBody(QDataStream &inStream)
{
    // Header Only messages
    if(currentHeader == "")
    {

    }

    // Header and Body messages
    inStream.startTransaction();
    if(currentHeader == "pageSignIn")
    {
        return processPageSignIn(inStream);
    }
    else if (currentHeader == "shipperOrderContracts")
    {
        return processPendingOrders(inStream);
    }
}

bool ClientBroker::processPageSignIn(QDataStream& inStream)
{
    QString pageName;
    inStream >> pageName;

    if(!inStream.commitTransaction())
        return false;

    emit(signInToPage(pageName));
    return true;
}

bool ClientBroker::processPendingOrders(QDataStream& inStream)
{
    QVector<OrderContract> orders;
    inStream >> orders;

    if(!inStream.commitTransaction())
        return false;

    emit(pendingOrderReceived(orders));
    return true;
}
