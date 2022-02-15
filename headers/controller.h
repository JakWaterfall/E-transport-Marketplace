#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include <QTcpSocket>
#include "serverbroker.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(ServerBroker* broker, QObject *parent = nullptr);

signals:

protected:
    ServerBroker* broker;
};

#endif // CONTEXT_H
