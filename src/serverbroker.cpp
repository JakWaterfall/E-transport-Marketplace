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

void ServerBroker::processLogIn(QJsonDocument messageJSON)
{
    qDebug() << "processing log in";
    auto [email, password] = parser.getLogInFromJSON(messageJSON);
    emit(logInAttempt(email, password));
}

void ServerBroker::processNewOrder(QJsonDocument orderContractJSON)
{
    OrderContract * contract = parser.orderContractFromJSON(orderContractJSON);
    //OrderContract * contract = new OrderContract(new Order("wqe", "wqe", "wqe", 1, true, "wqe"));
    //Order * order = new Order("wqe", "wqe", "wqe", 1, true, "wqe");
    if (contract)
    {
        qDebug() << "real";
    }
    emit(newOrderContract(contract));
}

void ServerBroker::sendOrderDetails(const QString & header, const QString &name, const QString &ID)
{
    sendMessage(parser.orderDetailsToJSON(header, name, ID));
}

void ServerBroker::sendPageSignIn(const QString pageName) const
{
    sendMessage(parser.pageSignInToJSON(pageName));
}

void ServerBroker::processMessage()
{
    while(socket->isReadable())
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

        if(header == "login")
        {
            processLogIn(messageJSON);
        }
        else if (header == "register")
        {

        }
        else if (header == "newOrder")
        {
            processNewOrder(messageJSON);
        }
        else if (header == "getShipperOrderScreen")
        {
            emit(requestForOrderDetails());
        }

    }
}

void ServerBroker::socketDisconnected()
{
    emit(disconnected());
}
