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

void ClientBroker::sendOrderToMarketplace(const OrderContract *orderContract)
{
    sendMessage(parser.orderContractToJSON(orderContract));
}

void ClientBroker::buildOrderScreen()
{
    sendMessage(parser.headerMessageToJSON("getShipperOrderScreen"));
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

void ClientBroker::processPageSignIn(QJsonDocument pageSignInJSON)
{
    QString pageName = pageSignInJSON["pageName"].toString();
    emit(signInToPage(pageName));
}

void ClientBroker::processPendingOrders(QJsonDocument pendingOrdersJSON)
{
    auto[name, ID] = parser.orderDetailsFromJSON(pendingOrdersJSON);

    emit(pendingOrder(name, ID));
}

void ClientBroker::processMessage()
{
    while (socket->isReadable())
    {
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

        if(header == "pageSignIn")
        {
            processPageSignIn(messageJSON);

        }
        else if (header == "register")
        {

        }
        else if (header == "pendingOrders")
        {
            processPendingOrders(messageJSON);
        }
    }
}

void ClientBroker::socketDisconnected()
{
    emit(disconnected());
}
