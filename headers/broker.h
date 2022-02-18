#ifndef BROKER_H
#define BROKER_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include "ordercontract.h"

class Broker : public QObject
{
    Q_OBJECT

protected:
    explicit Broker(QTcpSocket* socket, QObject *parent = nullptr);
    ~Broker();

protected:
    bool socketReady() const;
    bool readHeader(QDataStream& inStream);
    virtual bool readBody(QDataStream& inStream) = 0;

protected slots:
    void processMessage();
    void socketDisconnected();

signals:
    void disconnected();

protected:
    QTcpSocket* socket;
    QString currentHeader;
    bool headerAquired;
};

#endif // BROKER_H
