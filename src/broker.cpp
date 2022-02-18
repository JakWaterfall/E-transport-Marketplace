#include "broker.h"

Broker::Broker(QTcpSocket *socket, QObject *parent): QObject(parent), socket(socket), headerAquired(false)
{}

Broker::~Broker()
{
    socket->deleteLater();
}

bool Broker::readHeader(QDataStream &inStream)
{
    inStream.startTransaction();
    inStream >> currentHeader;
    if(inStream.commitTransaction())
    {
        return true;
    }
    else
        return false;
}

void Broker::processMessage()
{
    while(socket->isReadable())
    {
        qDebug() << "processing message";

        QDataStream inStream(socket);

        if(!headerAquired)
        {
            if(readHeader(inStream))
            {
                headerAquired = true;
            }
            else
                return; qDebug() << "waiting for more data";
        }

        if(readBody(inStream))
        {
            headerAquired = false;
        }
        else
            return; qDebug() << "waiting for more data";
    }
}

bool Broker::socketReady() const
{
    if (socket)
    {
        if (socket->isOpen())
        {
            return true;
        }
        else
            qDebug() << "socket is not open";
    }
    else
        qDebug() << "socket is not connected";
    return false;
}

void Broker::socketDisconnected()
{
    emit(disconnected());
}

