#include "database.h"

database::database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

database::~database(){
    db.close();
}

bool database::openMyDB(){
    db.setHostName("EtransportCompany");
    db.setDatabaseName("thisBase");
    db.setUserName("NSmith");
    db.setPassword("HelloWorld37");
    bool ok = db.open();
    return ok;
}

bool database::insertUserTable(QString firstName, QString lastName, QString email, QString password, QString address)
{
    QSqlQuery query2;
    query2.prepare("INSERT INTO User(firstName, lastName, email, password, address) "
                   "VALUES (?, ?, ?, ?, ?)");
    query2.bindValue(0, firstName);
    query2.bindValue(1, lastName);
    query2.bindValue(2, lastName);
    query2.bindValue(3, email);
    query2.bindValue(4, password);
    query2.bindValue(5, address);
    if(query2.exec()){
        qDebug() << "User table inserted";
    }
    else{
        qDebug() << "Error = " << query2.lastError().text();
    }
    return true;
}

bool database::containsAllTables(){
    QStringList myTables = db.tables();
    if(myTables.contains("User")){
        qDebug() << "Table user already here";
       }
    return true;
}

bool database::createUserTable(){
    bool ok;
    QSqlQuery query1;
    if(query1.exec("CREATE TABLE User(firstName VARCHAR(30), lastName VARCHAR(30), "
                   "email VARCHAR(40), password VARCHAR(40), address VARCHAR(50))")){
        ok = true;
    }
    else
    {
        qDebug() << "Error = " << query1.lastError().text();
        ok = false;
    }
    return ok;
}

bool database::createOrderTable(){
    return true;
}

bool database::createIdTable(){
    return true;
}


