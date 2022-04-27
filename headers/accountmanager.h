#ifndef ACCOUNTCONTROLLER_H
#define ACCOUNTCONTROLLER_H

#include <QObject>
#include <QCryptographicHash>
#include <shipper.h>
#include <forwarder.h>
#include <driver.h>
#include <database.h>

/**
 * @brief The AccountManager class that hold the logic dealing with user accounts.
 */
class AccountManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief The UserType enum which designates different user types.
     */
    enum UserType {ShipperUser, ForwarderUser, DriverUser};

public:
    explicit AccountManager(QObject *parent = nullptr);

    /**
     * @brief Verifies if user credentials are valid.
     * @param email The email of user.
     * @param password The password of user.
     * @return True if user credentials match in the system
     */
    bool verifyLogIn(QString email, QString password);

    /**
     * @brief Checks if an email is already registered in the system.
     * @param email The email to check.
     * @return True if email exists in the system.
     */
    bool emailExists(const QString& email);

    /**
     * @brief Gets the user type of a user by email
     * @param email The email to of the user to query.
     * @return The user type of the user.
     */
    UserType getUserType(QString email) const;

    /**
     * @brief Creates a user of type shipper. Thier data is pulled from the database using thier email.
     * @param email The email of the user.
     * @return The User.
     */
    Shipper createShipper(QString email);

    /**
     * @brief Creates a user of type forwarder. Thier data is pulled from the database using thier email.
     * @param email The email of the user.
     * @return The User.
     */
    Forwarder createForwarder(QString email);

    /**
     * @brief Creates a user of type driver. Thier data is pulled from the database using thier email.
     * @param email The email of the user.
     * @return The User.
     */
    Driver createDriver(QString email);

    /**
     * @brief Creates and places a user into the system database.
     * @param name The name of the user.
     * @param email The email of the user.
     * @param password The password of the user.
     * @param address The address of the user.
     * @param postcode The postcode of the user.
     * @param userType The user type of the user.
     */
    void createUser(const QString& name, const QString& email, const QString& password, const QString& address, const QString& postcode, const QString& userType);
signals:

private:
    /**
     * @brief Creates a vector of order IDs from a CSV string.
     * @param orderCSV The orderIDs in a CSV format.
     * @return The vector of order IDs.
     */
    QVector<QString> orderCSVToVector(QString& orderCSV);

};

#endif // ACCOUNTCONTROLLER_H
