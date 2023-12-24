#ifndef USER_H
#define USER_H

#include <QObject>
#include <QVector>

/**
 * @brief The User class is the base class of all the user types in the system.
 */
class User
{
public:
    /**
     * @brief User constuctor
     * @param name The name of the user.
     * @param email The email of the user.
     * @param address The address of the user.
     * @param postcode The postcode of the user.
     * @param ordersIDs The associated order IDs of the user.
     */
    User(QString name, QString email, QString address, QString postcode, QVector<QString> ordersIDs);
   ~User();

public:
    /**
     * @brief Returns the users name.
     * @return The name of the user.
     */
    const QString& getName();

    /**
     * @brief Returns the users email.
     * @return The email of the user.
     */
    const QString& getEmail();

    /**
     * @brief Returns the users address.
     * @return The address of the user.
     */
    const QString& getAddress();

    /**
     * @brief Returns the users postcode.
     * @return The postcode of the user.
     */
    const QString &getPostcode();

    /**
     * @brief Returns the users associated order IDs.
     * @return The order IDs associated with the user.
     */
    const QVector<QString> getOrderIDs();

    /**
     * @brief Adds a new order ID to the user.
     * @param ID The new order ID to be added.
     */
    void insertOrderID(QString ID);

    /**
     * @brief Removes an order ID from the user.
     * @param ID The order ID to be removed.
     */
    void removeOrderID(const QString& ID);

protected:
    QString name;
    QString email;
    QString address;
    QString postcode;

    QVector<QString> ordersIDs;
};

#endif // USER_H
