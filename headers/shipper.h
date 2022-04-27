#ifndef SHIPPER_H
#define SHIPPER_H

#include "user.h"
#include "order.h"
#include "ordercontract.h"
#include <QObject>
#include <QMap>

/**
 * @brief The Shipper class
 */
class Shipper : public User
{
public:
    /**
     * @brief Shipper constructor
     * @param name The name of the user.
     * @param email The email of the user.
     * @param address The address of the user.
     * @param postcode The postcode of the user.
     * @param ordersIDs The associated order IDs of the user.
     */
    Shipper(QString name, QString email, QString address, QString postcode, QVector<QString> orderIds);
    ~Shipper();

private:

};

#endif // SHIPPER_H
