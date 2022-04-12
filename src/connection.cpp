#include "connection.h"

Connection::Connection(QTcpSocket *socket, ThreadSafeMap<QString, OrderContract *> *marketplace, QObject *parent)
    : QThread(parent), broker(new ServerBroker(socket, this)), marketplace(marketplace), controller(nullptr), accountManager(AccountManager(this))
{}

Connection::~Connection()
{
    quit(); // Quit thread loop
    wait(); // wait till event queue has been excicuted before deleting objects
    broker->deleteLater();
    if (controller)
        controller->deleteLater();
}

void Connection::run()
{
//    qDebug() << "Thread started";
    connect(broker, &ServerBroker::disconnected, this, &Connection::brokerDisconnected);
    connect(broker, &ServerBroker::logInAttempt, this, &Connection::logIn);

    exec(); // Loops the thread to stay alive while connection is active
}

void Connection::changeSlotsAndSignalsToContext()
{
    disconnect(broker, &ServerBroker::logInAttempt, this, &Connection::logIn);
    // maybe disconnect broker disconnect here? unless it can save conext data to database before context is deleted?
}

void Connection::logIn(QString email, QString password)
{
    if(accountManager.verifyLogIn(email, password))
    {
        switch (accountManager.getUserType(email))
        {
        case AccountManager::UserType::ShipperUser:
            controller = new ShipperController(accountManager.createShipper(email, password), broker, marketplace, this);
            broker->sendPageSignIn("shipper");
            break;

        case AccountManager::UserType::ForwarderUser:
            // QString firstName, QString lastName, QString email, QString password, QString address
            controller = new ForwarderController(accountManager.createForwarder(email, password), broker, marketplace, this);
            broker->sendPageSignIn("forwarder");
            break;

        case AccountManager::UserType::DriverUser:
            controller = new DriverController(accountManager.createDriver(email, password), broker, marketplace, this);
            broker->sendPageSignIn("driver");
            break;
        }
        changeSlotsAndSignalsToContext();
    }
    else
    {
        broker->sendErrorMessage("Log In Credientails are incorrect");
    }
}

void Connection::brokerDisconnected()
{
    emit(disconnected(this));
}


// connection::register that calls log in if successful
