#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>

#include "connection.h"
#include "threadsafemap.h"

class Server : public QObject
{
    Q_OBJECT
public:
    /**
     *
     * @brief Constructor
     * @param parent The parent object for QT Framework
     */
    explicit Server(QObject *parent = nullptr);
    ~Server();

private slots:
    /**
     * @brief newConnection
     */
    void newConnection();
    /**
     * @brief removeConnection
     * @param connection
     */
    void removeConnection(Connection* connection);

signals:


private:
    ThreadSafeMap<QString, OrderContract*>* marketplace;
    QTcpServer* tcpServer;
    QVector<Connection*> connections;
};

#endif // SERVER_H
