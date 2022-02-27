#include "clientbroker.h"

ClientBroker::ClientBroker(QObject *parent) : Broker(new QTcpSocket(), parent)
{
    qDebug() << "ClientBroker created";
    socket->connectToHost(QHostAddress::LocalHost, 1234);
    // possibly waitForConnected here?

    connect(socket, &QTcpSocket::disconnected, this, &ClientBroker::socketDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &ClientBroker::processMessage);
}

void ClientBroker::logInAttempt(const QString& email, const QString& password)
{
    QString header = "login";
    if(socketReady())
    {
        QDataStream outStream(socket);
        outStream << header << email << password;
    }
}

void ClientBroker::sendOrderToMarketplace(const OrderContract& orderContract)
{
    QString header = "newOrder";
    if(socketReady())
    {
        QDataStream outStream(socket);
        outStream << header << orderContract;
    }
}

void ClientBroker::makeBidOnOrder(const QString &orderID, const OrderContract::Bid &bid)
{
    QString header = "newBid";
    if(socketReady())
    {
        QDataStream outStream(socket);
        outStream << header << orderID << bid;
    }
}

void ClientBroker::sendAcceptBidMessage(const QString &orderID, OrderContract::Bid &bid)
{
    QString header = "acceptBid";
    if(socketReady())
    {
        QDataStream outStream(socket);
        outStream << header << orderID << bid;
    }
}

void ClientBroker::acceptJob(const QString &orderID)
{
    QString header = "acceptJob";
    if(socketReady())
    {
        QDataStream outStream(socket);
        outStream << header << orderID;
    }
}

void ClientBroker::updateDeliveryState(const QString &orderID, const OrderContract::DeliveryState &deliveryState)
{
    QString header = "updateDeliveryState";
    if(socketReady())
    {
        QDataStream outStream(socket);
        outStream << header << orderID << deliveryState;
    }
}

void ClientBroker::requestOrderContracts()
{
    QString header = "requestOrderContracts";
    if(socketReady())
    {
        QDataStream outStream(socket);
        outStream << header;
    }
}

void ClientBroker::requestMarket()
{
    QString header = "requestMarket";
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
    else if (currentHeader == "orderContracts")
    {
        return processOrderContracts(inStream, &ClientBroker::ordersReceived);
    }
    else if (currentHeader == "marketOrders")
    {
        return processOrderContracts(inStream, &ClientBroker::marketReceived);
    }
    else if (currentHeader == "errorMessage")
    {
        return processErrorMessage(inStream);
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

bool ClientBroker::processErrorMessage(QDataStream &inStream)
{
    QString errorMessage;
    inStream >> errorMessage;

    if(!inStream.commitTransaction())
        return false;

    emit(receivedErrorMessage(errorMessage));
    return true;
}

bool ClientBroker::processOrderContracts(QDataStream& inStream, void(ClientBroker::*func)(QMap<QString, OrderContract>&)) // maybe make this a function template that has the emit functions as a parameter?
{
    QMap<QString, OrderContract> orders;
    inStream >> orders;

    if(!inStream.commitTransaction())
        return false;

    emit(this->*func)(orders);
    return true;
}
