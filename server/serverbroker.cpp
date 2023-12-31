#include "serverbroker.h"

ServerBroker::ServerBroker(QTcpSocket *socket, QObject *parent) : Broker(socket, parent)
{
    connect(socket, &QTcpSocket::disconnected, this, &ServerBroker::socketDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &ServerBroker::processMessage);
}

void ServerBroker::sendErrorMessage(const QString& message)
{
    QString header = "errorMessage";
    if(socketReady())
    {
        QDataStream outStream(socket);
        outStream << header << message;
    }
}

void ServerBroker::sendMessage(const QString &message)
{
    QString header = "message";
    if(socketReady())
    {
        QDataStream outStream(socket);
        outStream << header << message;
    }
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

bool ServerBroker::processRegister(QDataStream &inStream)
{
    QString name;
    QString email;
    QString password;
    QString confirmPass;
    QString address;
    QString postcode;
    QString userType;

    inStream >> name >> email >> password >> confirmPass >> address >> postcode >> userType;

    if(!inStream.commitTransaction())
        return false;

    emit(registerAttempt(name, email, password, confirmPass, address, postcode, userType));
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

bool ServerBroker::processNewBid(QDataStream &inStream)
{
    QString orderID;
    OrderContract::Bid bid;
    inStream >> orderID >> bid;

    if(!inStream.commitTransaction())
        return false;

    emit(newBidOnOrder(orderID, bid));
    return true;
}

bool ServerBroker::processAcceptBid(QDataStream &inStream)
{
    QString orderID;
    OrderContract::Bid bid;
    inStream >> orderID >> bid;

    if(!inStream.commitTransaction())
        return false;

    emit(acceptBid(orderID, bid));
    return true;
}

bool ServerBroker::processAcceptJob(QDataStream &inStream)
{
    QString orderID;
    inStream >> orderID;

    if(!inStream.commitTransaction())
        return false;

    emit(acceptJob(orderID));
    return true;
}

bool ServerBroker::processUpdateDeliveryState(QDataStream &inStream)
{
    QString orderID;
    OrderContract::DeliveryState deliveryState;
    inStream >> orderID >> deliveryState;

    if(!inStream.commitTransaction())
        return false;

    emit(updateDeliveryState(orderID, deliveryState));
    return true;
}

bool ServerBroker::readBody(QDataStream &inStream)
{
    // Header only messages
    if(currentHeader == "requestOrderContracts")
    {
        emit(requestForOrderContracts());
        return true;
    }
    else if (currentHeader == "requestMarket")
    {
        emit(requestForMarket());
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
        return processRegister(inStream);
    }
    else if (currentHeader == "newOrder")
    {
        return processNewOrder(inStream);
    }
    else if (currentHeader == "newBid")
    {
        return processNewBid(inStream);
    }
    else if (currentHeader == "acceptBid")
    {
        return processAcceptBid(inStream);
    }
    else if (currentHeader == "acceptJob")
    {
        return processAcceptJob(inStream);
    }
    else if (currentHeader == "updateDeliveryState")
    {
        return processUpdateDeliveryState(inStream);
    }
}

void ServerBroker::sendOrderContracts(const QString& header, const QMap<QString, OrderContract>& orders)
{
    if(socketReady())
    {
        QDataStream outStream(socket);
        outStream << header << orders;
    }
}

void ServerBroker::sendPageSignIn(const QString& pageName) const
{
    QString header = "pageSignIn";
    if(socketReady())
    {
        QDataStream outStream(socket);
        outStream << header << pageName;
    }
}

void ServerBroker::sendUserRelatedOrderContracts(const QMap<QString, OrderContract> &orders)
{
    sendOrderContracts("orderContracts", orders);
}

void ServerBroker::sendMarketOrderContracts(const QMap<QString, OrderContract> &marketOrders)
{
    sendOrderContracts("marketOrders", marketOrders);
}
