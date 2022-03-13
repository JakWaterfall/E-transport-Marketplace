#ifndef DATABASE_H
#define DATABASE_H

#include <QCoreApplication>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlError>

class database
{
public:
    database();
    ~database();
    bool openMyDB();

    // All insert functions for each table
    bool insertUserTable(QString firstName, QString lastName, QString email, QString password, QString address,
                         QString userType);
    bool insertOrderTable(int orderId, QString sourceAddress, QString destAddress, QString sourcePostcode,
                          QString destPostcode, int width, int height, int depth, int weight, bool fragile,
                          QString description, QString otherDetails, QDateTime &orderCreated);
    bool insertOrderContractTable(QString contractId, int orderId, QString shipperEmail, QString forwarderEmail,
                                  QString driverEmail, QString consigneeName, QString consigneeNumber,
                                  double finalBid, double finalDriverPrice, QString state, QString bids);
    bool insertInvoiceTable(int invoiceId, QString shipperName, QString forwarderName, QString shipperEmail,
                            QString forwarderEmail, QDateTime &date, QDateTime &dueDate, int price);

    // All delete fucntions for each table
    bool deleteFromUserTable();
    bool deleteFromOrderTable();
    bool deleteFromOrderContractTable();
    bool deleteFromInvoiceTable(QString shipperName, QString forwarderName, QDateTime &date);

    bool verifyLoginFromDatabase(QString email, QString password);
    // returns empty string "" if error occurs
    std::string getUserTypeFromDatabase(QString email);

    bool containsAllTables();

private:
    QSqlDatabase db;
    bool createUserTable();
    bool createOrderTable();
    bool createOrderContractTable();
    bool createInvoiceTable();
    bool createIdTable(); // REDUNDANT ATM

};

#endif // DATABASE_H
