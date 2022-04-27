#ifndef DRIVER_H
#define DRIVER_H

#include "user.h"

/**
 * @brief The Driver class
 */
class Driver : public User
{
public:
    /**
     * @brief Driver constructor
     * @param name The name of the user.
     * @param email The email of the user.
     * @param address The address of the user.
     * @param postcode The postcode of the user.
     * @param ordersIDs The associated order IDs of the user.
     */
    Driver(QString name, QString email, QString address, QString postcode, QVector<QString> orderIds);
};

#endif // DRIVER_H
