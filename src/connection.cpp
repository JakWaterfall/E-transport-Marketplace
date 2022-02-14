#include "connection.h"

Connection::Connection(QTcpSocket *socket, QMap<QString, OrderContract> *marketplace, QObject *parent)
    : QObject(parent), broker(new ServerBroker(socket, this)), marketplace(marketplace), context(nullptr), accountController(new AccountController(this))
{
    qDebug() << "connection created";
    connect(broker, &ServerBroker::disconnected, this, &Connection::brokerDisconnected);
    connect(broker, &ServerBroker::logInAttempt, this, &Connection::logIn);
}

Connection::~Connection()
{
    qDebug() << "Connection destroyed";
    broker->deleteLater();
    accountController->deleteLater();
    if (context)
        context->deleteLater();
}

void Connection::logIn(QString email, QString password)
{
//    if(accountController->verifyLogIn(email, password))
//    {
//        switch (accountController->getUserType(email))
//        {
//        case AccountController::UserType::ShipperUser:
//            context = new ShipperContext(accountController->getShipper(email, password), broker, this);
//            break;
//        }

//    }
//    else
//    {
//        // repost error to user
//        broker->sendErrorMessage(accountController->getError());

    //    }
}

void Connection::brokerDisconnected()
{
    emit(disconnected(this));
}


// connection::register that calls log in if successful
