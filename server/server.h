#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>

#include "connection.h"
#include "threadsafemap.h"

/**
 * @brief The Server class.
 */
class Server : public QObject
{
    Q_OBJECT
public:

    /**
     * Creates the Server object and sets up the TCP connection to listen for clients.
     * @brief Constructor
     * @param parent The parent object for QT Framework
     */
    explicit Server(QObject *parent = nullptr);
    ~Server();

private slots:

    /**
     * @brief Creates a new connection to a client and put it on its own thread.
     */
    void newConnection();

    /**
     * @brief Removes a connection from the system.
     * @param connection The connection to be removed.
     */
    void removeConnection(Connection* connection);

signals:


private:
    ThreadSafeMap<QString, OrderContract*>* marketplace;
    QTcpServer* tcpServer;
    QVector<Connection*> connections;
};

#endif // SERVER_H
