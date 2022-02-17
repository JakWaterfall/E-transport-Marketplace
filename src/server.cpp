#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    marketplace = new ThreadSafeMap<QString, OrderContract*>();
    tcpServer = new QTcpServer(this);
    if (tcpServer->listen(QHostAddress::Any, 1234))
    {
        connect(tcpServer, &QTcpServer::newConnection, this, &Server::newConnection);
        qDebug() << "server connected!";
    }
    else
    {
        qDebug() << "server did not work!";
    }
}

Server::~Server()
{
    // save all marketplace to database
    for(auto& connection: connections)
        connection->deleteLater();
    tcpServer->deleteLater();
}

void Server::newConnection()
{
    auto connection = new Connection(tcpServer->nextPendingConnection(), marketplace, this);
    connect(connection, &Connection::disconnected, this, &Server::removeConnection);
    connections.push_back(connection);
    qDebug() << "new connection";
}

void Server::removeConnection(Connection *connection)
{
    connection->deleteLater();
    connections.erase(std::remove(std::begin(connections), std::end(connections), connection), std::end(connections));
}
