#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include <QTcpSocket>
#include "serverbroker.h"

class Context : public QObject
{
    Q_OBJECT
public:
    explicit Context(ServerBroker* broker, QObject *parent = nullptr);

signals:

protected:
    ServerBroker* broker;
};

#endif // CONTEXT_H
