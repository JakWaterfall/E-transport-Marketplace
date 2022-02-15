#include "connection.h"

Connection::Connection(QTcpSocket *socket, QMap<QString, OrderContract> *marketplace, QObject *parent)
    : QObject(parent), broker(new ServerBroker(socket, this)), marketplace(marketplace), controller(nullptr), accountManager(new AccountManager(this))
{
    qDebug() << "connection created";
    connect(broker, &ServerBroker::disconnected, this, &Connection::brokerDisconnected);
    connect(broker, &ServerBroker::logInAttempt, this, &Connection::logIn);
}

Connection::~Connection()
{
    qDebug() << "Connection destroyed";
    broker->deleteLater();
    accountManager->deleteLater();
    if (controller)
        controller->deleteLater();
}

void Connection::changeSlotsAndSignalsToContext()
{
    disconnect(broker, &ServerBroker::logInAttempt, this, &Connection::logIn);
    // maybe disconnect broker disconnect here? unless it can save conext data to database before context is deleted?
}

void Connection::logIn(QString email, QString password)
{
    qDebug() << "Log in attempt";
    if(accountManager->verifyLogIn(email, password))
    {
        switch (accountManager->getUserType(email))
        {
        case AccountManager::UserType::ShipperUser:
            controller = new ShipperController(accountManager->createShipper(email, password), broker, this);
            break;
            // change this to forwarder controller
        case AccountManager::UserType::ForwarderUser:
            controller = new ShipperController(accountManager->createShipper(email, password), broker, this);
            break;
        }
        changeSlotsAndSignalsToContext();
    }
    else
    {
        // repost error to user
        //broker->sendErrorMessage(accountController->getError());

    }
}

void Connection::brokerDisconnected()
{
    emit(disconnected(this));
}


// connection::register that calls log in if successful
