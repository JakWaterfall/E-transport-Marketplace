#include "clientbroker.h"

ClientBroker::ClientBroker(QObject *parent) : Broker(new QTcpSocket(), parent)
{
    qDebug() << "ClientBroker created";
    socket->connectToHost(QHostAddress::LocalHost, 1234);

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

void ClientBroker::registerAttempt(const QString &name, const QString &email, const QString &password, const QString &confirmPassword, const QString &address, const QString &postcode, const QString &userType)
{
    QString header = "register";
    if(socketReady())
    {
        QDataStream outStream(socket);
        outStream << header << name << email << password << confirmPassword << address << postcode << userType;
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
    // Header and Body messages
    inStream.startTransaction();
    if(currentHeader == "pageSignIn")
    {
        return processPageSignIn(inStream);
    }
    else if (currentHeader == "orderContracts") // The 4 methods below also take a function pointer to the signal that will be emitted.
    {
        return processOrderContracts(inStream, &ClientBroker::ordersReceived);
    }
    else if (currentHeader == "marketOrders")
    {
        return processOrderContracts(inStream, &ClientBroker::marketReceived);
    }
    else if (currentHeader == "errorMessage")
    {
        return processNewMessage(inStream, &ClientBroker::receivedErrorMessage);
    }
    else if (currentHeader == "message")
    {
        return processNewMessage(inStream, &ClientBroker::receivedMessage);
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

bool ClientBroker::processOrderContracts(QDataStream& inStream, void(ClientBroker::*func)(QMap<QString, OrderContract>&))
{
    QMap<QString, OrderContract> orders;
    inStream >> orders;

    if(!inStream.commitTransaction())
        return false;

    emit(this->*func)(orders); // Emit the signal that was passed as a function pointer
    return true;
}

bool ClientBroker::processNewMessage(QDataStream &inStream, void (ClientBroker::*func)(const QString &))
{
    QString message;
    inStream >> message;

    if(!inStream.commitTransaction())
        return false;

    emit(this->*func)(message); // Emit the signal that was passed as a function pointer
    return true;
}
