#include "controller.h"

Controller::Controller(ServerBroker* broker, ThreadSafeMap<QString, OrderContract *> *marketplace, QObject *parent)
    : QObject(parent), broker(broker), marketplace(marketplace)
{}

void Controller::saveOrderIdsToDatabase(const QString &email, const QVector<QString> orderIds)
{
    QString orderIdsCSV;

    for(auto i = std::begin(orderIds); i != std::end(orderIds); i++)
    {
        if(i != std::begin(orderIds))
            orderIdsCSV += ",";

        orderIdsCSV += *i;
    }

    database db;
    db.insertUserOrderIds(email, orderIdsCSV);
}
