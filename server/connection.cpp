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
    connect(broker, &ServerBroker::disconnected, this, &Connection::brokerDisconnected);
    connect(broker, &ServerBroker::logInAttempt, this, &Connection::logIn);
    connect(broker, &ServerBroker::registerAttempt, this, &Connection::registerAttempt);

    exec(); // Loops the thread to stay alive while connection is active
}

void Connection::changeSlotsAndSignalsToContext()
{
    disconnect(broker, &ServerBroker::logInAttempt, this, &Connection::logIn);
    disconnect(broker, &ServerBroker::registerAttempt, this, &Connection::registerAttempt);
}

void Connection::logIn(QString email, QString password)
{
    if(accountManager.verifyLogIn(email, password))
    {
        switch (accountManager.getUserType(email))
        {
        case AccountManager::UserType::ShipperUser:
            controller = new ShipperController(accountManager.createShipper(email), broker, marketplace, this);
            broker->sendPageSignIn("shipper");
            break;

        case AccountManager::UserType::ForwarderUser:
            controller = new ForwarderController(accountManager.createForwarder(email), broker, marketplace, this);
            broker->sendPageSignIn("forwarder");
            break;

        case AccountManager::UserType::DriverUser:
            controller = new DriverController(accountManager.createDriver(email), broker, marketplace, this);
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

void Connection::registerAttempt(QString name, QString email, QString password, QString confirmPass, QString address, QString postcode, QString userType)
{
    // verify no black enties
    if(name.isEmpty() || email.isEmpty() || password.isEmpty() || confirmPass.isEmpty() || address.isEmpty() || postcode.isEmpty())
    {
        broker->sendErrorMessage("Must fill out each input to register");
        return;
    }

    if(accountManager.emailExists(email))
    {
        broker->sendErrorMessage("Email is already registered with this system. Try Logging in.");
        return;
    }

    // Test email aganst regex
    QRegExp emailRegEx("^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$");
    if(!emailRegEx.exactMatch(email))
    {
        broker->sendErrorMessage("Incorrect format for email.");
        return;
    }

    // Test Password
    QRegExp passRegEx("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}$");
    if(!passRegEx.exactMatch(password))
    {
        broker->sendErrorMessage("Incorrect format for password. Password must contain at least 1 uppercase and lowercase letter and 1 number.");
        return;
    }

    if(password != confirmPass)
    {
        broker->sendErrorMessage("The passwords provided do not match.");
        return;
    }

    accountManager.createUser(name, email, password, address, postcode, userType);
    logIn(email, password);

}

void Connection::brokerDisconnected()
{
    emit(disconnected(this));
}


// connection::register that calls log in if successful
