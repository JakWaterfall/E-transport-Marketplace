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
    // QStringList allTables = {};
    QStringList myTables = db.tables();
    if(myTables.contains("User")){
        qDebug() << "Table user already here";
       }
    return true;
}

bool database::createUserTable(){
    bool ok;
    QSqlQuery query1;
    if(query1.exec("CREATE TABLE User(userId INT, firstName TEXT, lastName TEXT, "
                   "email TEXT, password TEXT, address TEXT, userType TEXT), orderIds")){
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
    bool ok;
    QSqlQuery query1;
    if(query1.exec("CREATE TABLE Order(orderId INT, sourceAddress TEXT, destAddress TEXT, "
                   "sourcePostcode TEXT, destPostcode TEXT, width INT, height INT), "
                   "depth INT, weight INT, fragile BOOLEAN, description TEXT, "
                   "otherDetails TEXT, orderCreated DATETIME")){
        ok = true;
    }
    else
    {
        qDebug() << "Error = " << query1.lastError().text();
        ok = false;
    }
    return ok;
}

bool createOrderContractTable(){
    bool ok;
    QSqlQuery query1;
    if(query1.exec("CREATE TABLE OrderContract(contractId INT, orderId INT, "
                   "shipperEmail TEXT, forwarderEmail TEXT, driverEmail TEXT, "
                   "consigneeName TEXT, consigneeNumber TEXT, finalBid DOUBLE, "
                   "finalDriverPrice DOUBLE, state TEXT, bids")){
        ok = true;
    }
    else
    {
        qDebug() << "Error = " << query1.lastError().text();
        ok = false;
    }
    return ok;
}

bool createInvoiceTable(){
    bool ok;
    QSqlQuery query1;
    if(query1.exec("CREATE TABLE OrderContract(invoiceId INT, shipperName TEXT, "
                   "forwarderName TEXT, shipperEmail TEXT, forwarderEmail TEXT, "
                   "date DATETIME, dueDate DATETIME, price INT")){
        ok = true;
    }
    else
    {
        qDebug() << "Error = " << query1.lastError().text();
        ok = false;
    }
    return ok;
}

bool database::createIdTable(){
    return true;
}


