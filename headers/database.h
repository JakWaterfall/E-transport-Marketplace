#ifndef DATABASE_H
#define DATABASE_H

#include <QCoreApplication>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlError>

struct OrderData {
    int orderId;
    QString sourceAddress;
    QString destAddress;
    QString sourcePostcode;
    QString destPostcode;
    int width;
    int height;
    int depth;
    int weight;
    bool fragile;
    QString description;
    QString otherDetails;
    QDateTime orderCreated();
};

struct OrderContractData {
    QString contractId;
    int orderId;
    QString shipperEmail;
    QString forwarderEmail;
    QString driverEmail;
    QString consigneeName;
    QString consigneeNumber;
    double finalBid;
    double finalDriverPrice;
    QString state;
    QString bids;
};

class database
{
public:
    database();
    ~database();

    // All insert functions for each table
    // Binds inputted column vaiables to the insert statement and then executes the insert on the database
    bool insertUserTable(QString name, QString email, QString password, QString address, QString postcode, QString userType);
    bool insertOrderTable(int orderId, QString sourceAddress, QString destAddress, QString sourcePostcode,
                          QString destPostcode, int width, int height, int depth, int weight, bool fragile,
                          QString description, QString otherDetails, QDateTime &orderCreated);
    bool insertOrderContractTable(QString contractId, int orderId, QString shipperEmail, QString forwarderEmail,
                                  QString driverEmail, QString consigneeName, QString consigneeNumber,
                                  double finalBid, double finalDriverPrice, QString state, QString bids);
    bool insertInvoiceTable(int invoiceId, QString shipperName, QString forwarderName, QString shipperEmail,
                            QString forwarderEmail, QDateTime &date, QDateTime &dueDate, int price);
    void insertUserOrderIds(const QString& email, const QString& orderIds);


    // All delete fucntions for each table
    bool deleteFromUserTable();
    bool deleteFromOrderTable();
    bool deleteFromOrderContractTable();
    // The only delete that is implemented so far
    bool deleteFromInvoiceTable(QString shipperName, QString forwarderName, QDateTime &date);


    // These are the fucntions that use SELECT
    bool emailExists(const QString& email);

    // returns empty string "" if error occurs
    QString getUserType(const QString& email);
    QString getPassword(const QString& email);
    QStringList getUserDetails(const QString& email);


    bool updateOrderTable(int orderId, QString sourceAddress, QString destAddress, QString sourcePostcode,
                          QString destPostcode, int width, int height, int depth, int weight, bool fragile,
                          QString description, QString otherDetails, QDateTime &orderCreated);
    bool updateOrderContractTable(QString contractId, int orderId, QString shipperEmail, QString forwarderEmail,
                                  QString driverEmail, QString consigneeName, QString consigneeNumber,
                                  double finalBid, double finalDriverPrice, QString state, QString bids);

    OrderData selectOrderTable(int orderId);
    OrderContractData selectOrderContractTable(QString contractId);

private:
    QSqlDatabase db;
    void createTables();

    bool createInvoiceTable();
    bool createIdTable(); // REDUNDANT ATM

    QString getUserValueByEmail(const QString& tableColumnName, const QString& email);
};

#endif // DATABASE_H
