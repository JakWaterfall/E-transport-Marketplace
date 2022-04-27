#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QThread>

#include "shippercontroller.h"
#include "forwardercontroller.h"
#include "drivercontroller.h"
#include "accountmanager.h"
#include "serverbroker.h"
#include "threadsafemap.h"

/**
 * @brief The Connection class used t house all the logic a connection from a client needs.
 */
class Connection : public QThread
{
    Q_OBJECT
public:
    /**
     * @brief Connection Constructor
     * @param socket The TCP socket that connects to the client.
     * @param marketplace The marketplace of orders which is shared between conecctions.
     * @param parent The parent object for QT Framework.
     */
    explicit Connection(QTcpSocket* socket, ThreadSafeMap<QString, OrderContract*>* marketplace, QObject *parent = nullptr);
    ~Connection();

    /**
     * Sets up basic connection slots and signals.
     * @brief Begins running the thread.
     */
    void run() override;

private:
    /**
     * @brief Removes the login and register signles.
     */
    void changeSlotsAndSignalsToContext();

signals:
    /**
     * @brief Disconnected signal used for when the server broker has disconnected.
     * @param connection The connection which is disconnecting.
     */
    void disconnected(Connection* connection);

private slots:
    /**
     * @brief Logs user into the system.
     * @param email The email of the user logging in.
     * @param password The password of the user logging in.
     */
    void logIn(QString email, QString password);

    /**
     * @brief Registers the user into the system.
     * @param name The name of the user.
     * @param email The email of the user.
     * @param password The password of the user.
     * @param confirmPass The password to match with.
     * @param address The address of the user.
     * @param postcode The postcode of the user.
     * @param userType The user type (shipper, forwarder or driver) of the user.
     */
    void registerAttempt(QString name, QString email, QString password, QString confirmPass, QString address, QString postcode, QString userType);

    /**
     * @brief Triggers the signal to tell the system that the connection has disconnected.
     */
    void brokerDisconnected();

private:
    ServerBroker* broker;
    ThreadSafeMap<QString, OrderContract*>* marketplace;
    Controller* controller;
    AccountManager accountManager;
};

#endif // CONNECTION_H
