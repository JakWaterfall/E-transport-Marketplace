#ifndef DATABASE_H
#define DATABASE_H

#include <QCoreApplication>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlError>

/**
 * @brief The database class holds all the logic for sending and retrieving infomation from the database.
 */
class database
{
public:
    /**
     * @brief database Constructor.
     */
    database();
    ~database();

    /**
     * @brief Inserts a new row into the user table.
     * @param name The name of the user.
     * @param email The email of the user.
     * @param password The password of the user.
     * @param address The address of the user.
     * @param postcode The postcode of the user.
     * @param userType The user type of the user.(Shipper, Forwarder or Driver)
     */
    void insertUserTable(QString name, QString email, QString password, QString address, QString postcode, QString userType);

    /**
     * @brief Inserts the users related IDs into the user table.
     * @param email The email of the user whos order IDs are being inserted.
     * @param orderIds The order IDs beinf inserted
     */
    void insertUserOrderIds(const QString& email, const QString& orderIds);

    /**
     * @brief Tests if a email exists in the database.
     * @param email The emails being tested.
     * @return True of the email exists in the database.
     */
    bool emailExists(const QString& email);

    /**
     * @brief Returns a users user type by email.
     * @param email The email of the user.
     * @return The user type(Shipper, Forwarder or Driver) of the user.
     */
    QString getUserType(const QString& email);

    /**
     * @brief Returns a users password by email.
     * @param email The email of the user.
     * @return The password of the user.
     */
    QString getPassword(const QString& email);

    /**
     * @brief Returns all of a users details by email.
     * @param email The email of the user.
     * @return All of the users details. (name, email, address, postcode, order IDs)
     */
    QStringList getUserDetails(const QString& email);

private:
    /**
     * @brief Creates the database tables.
     */
    void createTables();

    /**
     * @brief Returns a value in the user table by email.
     * @param tableColumnName The column name of the value to be returned.
     * @param email The email of the user to be queried.
     * @return The value of the column name.
     */
    QString getUserValueByEmail(const QString& tableColumnName, const QString& email);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
