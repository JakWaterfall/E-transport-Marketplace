 #include "database.h"

database::database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    containsAllTables();
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

bool database::insertUserTable(QString firstName, QString lastName, QString email, QString password, QString address, QString userType)
{
    QSqlQuery query2;
    query2.prepare("INSERT INTO User(firstName, lastName, email, password, address, userType) "
                   "VALUES (?, ?, ?, ?, ?, ?)");
    query2.bindValue(0, firstName);
    query2.bindValue(1, lastName);
    query2.bindValue(2, email);
    query2.bindValue(3, password);
    query2.bindValue(4, address);
    query2.bindValue(5, userType);
    if(query2.exec()){
        qDebug() << "User table inserted";
        return true;
    }
    else{
        qDebug() << "Error = " << query2.lastError().text();
        return false;
    }
}

bool insertOrderTable(int orderId, QString sourceAddress, QString destAddress, QString sourcePostcode,
                      QString destPostcode, int width, int height, int depth, int weight, bool fragile,
                      QString description, QString otherDetails, QDateTime &orderCreated){
    QSqlQuery query2;
    query2.prepare("INSERT INTO Order(orderId, sourceAddress, destAddress, sourcePostcode, destPostcode, width, "
                   "height, depth, weight, fragile, description, otherDetails, orderCreated) "
                   "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query2.bindValue(0, orderId);
    query2.bindValue(1, sourceAddress);
    query2.bindValue(2, destAddress);
    query2.bindValue(3, sourcePostcode);
    query2.bindValue(4, destPostcode);
    query2.bindValue(5, width);
    query2.bindValue(6, height);
    query2.bindValue(7, depth);
    query2.bindValue(8, weight);
    query2.bindValue(9, fragile);
    query2.bindValue(10, description);
    query2.bindValue(11, otherDetails);
    query2.bindValue(12, orderCreated);
    if(query2.exec()){
        qDebug() << "User table inserted";
        return true;
    }
    else{
        qDebug() << "Error = " << query2.lastError().text();
        return false;
    }
}

bool insertOrderContractTable(QString contractId, int orderId, QString shipperEmail, QString forwarderEmail,
                              QString driverEmail, QString consigneeName, QString consigneeNumber,
                              double finalBid, double finalDriverPrice, QString state, QString bids){
    QSqlQuery query2;
    query2.prepare("INSERT INTO OrderContract(contractId, orderId, shipperEmail, forwarderEmail, driverEmail, consigneeName, "
                   "consigneeNumber, finalBid, finalDriverPrice, state, bids) "
                   "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query2.bindValue(0, contractId);
    query2.bindValue(1, orderId);
    query2.bindValue(2, shipperEmail);
    query2.bindValue(3, forwarderEmail);
    query2.bindValue(4, driverEmail);
    query2.bindValue(5, consigneeName);
    query2.bindValue(6, consigneeNumber);
    query2.bindValue(7, finalBid);
    query2.bindValue(8, finalDriverPrice);
    query2.bindValue(9, state);
    query2.bindValue(10, bids);
    if(query2.exec()){
        qDebug() << "User table inserted";
        return true;
    }
    else{
        qDebug() << "Error = " << query2.lastError().text();
        return false;
    }
}

bool insertInvoiceTable(int invoiceId, QString shipperName, QString forwarderName, QString shipperEmail,
                        QString forwarderEmail, QDateTime &date, QDateTime &dueDate, int price){
    QSqlQuery query2;
    query2.prepare("INSERT INTO Invoice(invoiceId, shipperName, forwarderName, shipperEmail, forwarderEmail, date, "
                   "dueDate, price) "
                   "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    query2.bindValue(0, invoiceId);
    query2.bindValue(1, shipperName);
    query2.bindValue(2, forwarderName);
    query2.bindValue(3, shipperEmail);
    query2.bindValue(4, forwarderEmail);
    query2.bindValue(5, date);
    query2.bindValue(6, dueDate);
    query2.bindValue(7, price);
    if(query2.exec()){
        qDebug() << "User table inserted";
        return true;
    }
    else{
        qDebug() << "Error = " << query2.lastError().text();
        return false;
    }
}

bool deleteFromUserTable(){
    // STUB DEFINITION
    return true;
}

bool deleteFromOrderTable(){
    // STUB DEFINITION
    return true;
}

bool deleteFromOrderContractTable(){
    // STUB DEFINITION
    return true;
}

bool deleteFromInvoiceTable(QString shipperName, QString forwarderName, QDateTime &date){
    QSqlQuery query1;
    query1.prepare("DELETE FROM Invoice WHERE shipperName = ? AND forwarderName = ? AND date = ?");
    query1.bindValue(0, shipperName);
    query1.bindValue(1, forwarderName);
    query1.bindValue(2, date);
    if(query1.exec()){
        return true;
    }
    else
    {
        qDebug() << "Error = " << query1.lastError().text();
        return false;
    }
}

bool verifyLoginFromDatabase(QString email, QString password){
    // INSERT INTO User(firstName, lastName, email, password, address, userType)
    bool ok = false;
    QSqlQuery query1;
    query1.prepare("SELECT password FROM User WHERE email = ?");
    query1.bindValue(0, email);
    if(!query1.exec()){
        qDebug() << "Error = " << query1.lastError().text();
    }
    else {
        query1.next();
        QString actualPassword = query1.value(0).toString();
        if(actualPassword == password){
            ok = true;
        }
    }
    return ok;
}

QString getUserTypeFromDatabase(QString email){
    // INSERT INTO User(firstName, lastName, email, password, address, userType)
    QSqlQuery query1;
    query1.prepare("SELECT userType FROM User WHERE email = ?");
    query1.bindValue(0, email);
    if(!query1.exec()){
        qDebug() << "Error = " << query1.lastError().text();
    }
    else {
        query1.next();
        QString thisUserType = query1.value(0).toString();
        return thisUserType;
    }
    return "";
}

bool database::containsAllTables(){
    QStringList allTables = {"User", "Order", "OrderContract", "Invoice"};
    QStringList myTables = db.tables();
    for(int i = 0; i < 4; i++){
        if(!myTables.contains(allTables[i])){
            qDebug() << "Table not here: " << allTables[i];
            if(i == 0){
                qDebug() << "Creating User table";
                createUserTable();
            }
            else if(i == 1){
                qDebug() << "Creating Order table";
                createOrderTable();
            }
            else if(i == 2){
                qDebug() << "Creating OrderContract table";
                createOrderContractTable();
            }
            else if(i == 3){
                qDebug() << "Creating Invoice table";
                createInvoiceTable();
            }
            else{
                qDebug() << "Error: table with index 4 or above does not exist";
            }
           }
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

bool database::createOrderContractTable(){
    bool ok;
    QSqlQuery query1;
    if(query1.exec("CREATE TABLE OrderContract(contractId TEXT, orderId INT, "
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

bool database::createInvoiceTable(){
    bool ok;
    QSqlQuery query1;
    if(query1.exec("CREATE TABLE Invoice(invoiceId INT, shipperName TEXT, "
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

// REDUNDANT ATM
bool database::createIdTable(){
    return true;
}


