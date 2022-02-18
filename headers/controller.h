#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include "serverbroker.h"
#include "threadsafemap.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(ServerBroker* broker, ThreadSafeMap<QString, OrderContract *> *marketplace, QObject *parent = nullptr);

signals:

protected:
    ServerBroker* broker;
    ThreadSafeMap<QString, OrderContract *> *marketplace;
};

#endif // CONTEXT_H
