#ifndef FORWARDER_H
#define FORWARDER_H

#include "user.h"
#include "order.h"
#include "ordercontract.h"
#include <QObject>
#include <QMap>

/**
 * @brief The Forwarder class
 */
class Forwarder : public User
{
public:
    /**
     * @brief Forwarder constructor
     * @param name The name of the user.
     * @param email The email of the user.
     * @param address The address of the user.
     * @param postcode The postcode of the user.
     * @param ordersIDs The associated order IDs of the user.
     */
    Forwarder(QString name, QString email, QString address, QString postcode, QVector<QString> orderIds);
    ~Forwarder();
private:
};

#endif // FORWARDER_H
