#include "controller.h"

Controller::Controller(ServerBroker* broker, ThreadSafeMap<QString, OrderContract *> *marketplace, QObject *parent)
    : QObject(parent), broker(broker), marketplace(marketplace)
{}
