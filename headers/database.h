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
    bool insertUserTable(QString firstName, QString lastName, QString email, QString password, QString address);
    bool containsAllTables();

private:
    QSqlDatabase db;
    bool createUserTable();
    bool createOrderTable();
    bool createOrderContractTable();
    bool createIdTable();

};

#endif // DATABASE_H
