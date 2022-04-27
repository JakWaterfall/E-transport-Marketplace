#ifndef BROKER_H
#define BROKER_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include "ordercontract.h"

/**
 * @brief The Broker class is the parent class of the client and server brokers. It holds logic that is needed by both.
 */
class Broker : public QObject
{
    Q_OBJECT

protected:
    /**
     * @brief Broker constructor
     * @param socket The TCP socket that connects client and server.
     * @param parent The parent object for QT Framework.
     */
    explicit Broker(QTcpSocket* socket, QObject *parent = nullptr);
    ~Broker();

protected:
    /**
     * @brief Tests if the socket is ready for use.
     * @returnTrue if the socket is open and ready.
     */
    bool socketReady() const;

    /**
     * @brief Reads the header of an incomming message.
     * @param inStream The datastream of the socket for incoming messages.
     * @return True if the header was successfully read.
     */
    bool readHeader(QDataStream& inStream);

    /**
     * @brief Abstract method that the client or server broekr must override. Reads the body of the message after the header.
     * @param inStream The datastream of the socket for incoming messages.
     * @return True if the body was successfully read.
     */
    virtual bool readBody(QDataStream& inStream) = 0;

protected slots:
    /**
     * @brief Processes an incoming message be first reading the header and then the body.
     */
    void processMessage();

    /**
     * @brief Emits a signal if the TCP socket disconnects.
     */
    void socketDisconnected();

signals:
    /**
     * @brief disconnected Signal
     */
    void disconnected();

protected:
    QTcpSocket* socket;
    QString currentHeader;
    bool headerAquired;
};

#endif // BROKER_H
