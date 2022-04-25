 #include "database.h"

database::database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    auto dbPath = qApp->applicationDirPath() + "E-TransportDa"
                                               "tabase.db";
    db.setDatabaseName(dbPath);
    db.open();

    createTables();
}

database::~database(){
    db.close();
    auto dbName = db.connectionName();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase(dbName);
    qDebug() << "Database Destroyed";
}

bool database::database::insertUserTable(QString name, QString email, QString password, QString address, QString postcode, QString userType)
{
    QSqlQuery query2;
    query2.prepare("INSERT INTO User(Name, Email, Password, address, postcode, userType) "
                   "VALUES (?, ?, ?, ?, ?, ?)");
    query2.bindValue(0, name);
    query2.bindValue(1, email);
    query2.bindValue(2, password);
    query2.bindValue(3, address);
    query2.bindValue(4, postcode);
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

bool database::insertOrderTable(int orderId, QString sourceAddress, QString destAddress, QString sourcePostcode,
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
        qDebug() << "Order table inserted";
        return true;
    }
    else{
        qDebug() << "Error = " << query2.lastError().text();
        return false;
    }
}

bool database::insertOrderContractTable(QString contractId, int orderId, QString shipperEmail, QString forwarderEmail,
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
        qDebug() << "OrderContract table inserted";
        return true;
    }
    else{
        qDebug() << "Error = " << query2.lastError().text();
        return false;
    }
}

bool database::insertInvoiceTable(int invoiceId, QString shipperName, QString forwarderName, QString shipperEmail,
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
        qDebug() << "Invoice table inserted";
        return true;
    }
    else{
        qDebug() << "Error = " << query2.lastError().text();
        return false;
    }
}

void database::insertUserOrderIds(const QString &email, const QString &orderIds)
{
    qDebug() << "running insert to orderid";

    QSqlQuery query2;
    query2.prepare("UPDATE User SET orderIds = ? WHERE Email = ?");
    query2.bindValue(0, orderIds);
    query2.bindValue(1, email);

    if(!query2.exec())
        qDebug() << "Error = " << query2.lastError().text();
}

bool database::deleteFromUserTable(){
    // STUB DEFINITION
    return true;
}

bool database::deleteFromOrderTable(){
    // STUB DEFINITION
    return true;
}

bool database::deleteFromOrderContractTable(){
    // STUB DEFINITION
    return true;
}

bool database::deleteFromInvoiceTable(QString shipperName, QString forwarderName, QDateTime &date){
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

bool database::emailExists(const QString &email)
{
    QSqlQuery emailQuery;
    emailQuery.prepare("SELECT Email FROM User WHERE Email = ?");
    emailQuery.bindValue(0, email);

    if(!emailQuery.exec())
    {
        qDebug() << "Error = " << emailQuery.lastError().text();
        return false;
    }
    else
    {
        return emailQuery.next();
    }
}


QString database::getUserType(const QString &email)
{
    return getUserValueByEmail("userType", email);
}

QString database::getPassword(const QString &email)
{
    return getUserValueByEmail("Password", email);
}

QStringList database::getUserDetails(const QString &email)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM User WHERE Email = ?");
    query.bindValue(0, email);

    if(!query.exec())
        qDebug() << "Error = " << query.lastError().text();

    if(query.next())
    {
        auto name = query.value(0).toString();
        auto email = query.value(1).toString();
        auto address = query.value(3).toString();
        auto postcode = query.value(4).toString();
        auto orderIds = query.value(6).toString();

        return {name, email, address, postcode, orderIds};
    }
    else
    {
        return {};
    }
}

void database::createTables()
{
    QString userTableStr = "create table if not exists User(Name TEXT, Email TEXT PRIMARY KEY, Password TEXT, address TEXT, postcode TEXT, userType TEXT, orderIds TEXT)";
    QString orderTableStr = "create table if not exists Orders(Id TEXT PRIMARY KEY, sourceAddress TEXT, destAddress TEXT, sourcePostcode TEXT, destPostcode TEXT, width INT, height INT, depth INT, weight INT, fragile TEXT, description TEXT, otherDetails TEXT, orderCreated TEXT)";
    QString orderContractTableStr = "create table if not exists OrderContract(Id TEXT PRIMARY KEY, orderId INT, shipperEmail TEXT, forwarderEmail TEXT, driverEmail TEXT, consigneeName TEXT, consigneeNumber TEXT, finalBid DOUBLE, finalDriverPrice DOUBLE, state TEXT, bids TEXT)";

    QStringList createTableQueries = {userTableStr, orderTableStr, orderContractTableStr};

    QSqlQuery createTableQuery;
    for(auto i = 0; i < createTableQueries.size(); i++)
    {
        if(!createTableQuery.exec(createTableQueries[i]))
        {
            qDebug() << "Error = " << createTableQuery.lastError().text();
        }
    }
}

bool database::updateOrderTable(int orderId, QString sourceAddress, QString destAddress, QString sourcePostcode,
                      QString destPostcode, int width, int height, int depth, int weight, bool fragile,
                      QString description, QString otherDetails, QDateTime &orderCreated){
    QSqlQuery query2;
    query2.prepare("UPDATE Order SET sourceAddress = ?, destAddress = ?, sourcePostcode = ?, destPostcode = ?, width = ?, "
                   "height = ?, depth = ?, weight = ?, fragile = ?, description = ?, otherDetails = ?, orderCreated = ? "
                   "WHERE orderId = ?");
    query2.bindValue(0, sourceAddress);
    query2.bindValue(1, destAddress);
    query2.bindValue(2, sourcePostcode);
    query2.bindValue(3, destPostcode);
    query2.bindValue(4, width);
    query2.bindValue(5, height);
    query2.bindValue(6, depth);
    query2.bindValue(7, weight);
    query2.bindValue(8, fragile);
    query2.bindValue(9, description);
    query2.bindValue(10, otherDetails);
    query2.bindValue(11, orderCreated);
    query2.bindValue(12, orderId);
    if(query2.exec()){
        qDebug() << "Order table updated";
        return true;
    }
    else{
        qDebug() << "Error = " << query2.lastError().text();
        return false;
    }
}

bool database::updateOrderContractTable(QString contractId, int orderId, QString shipperEmail, QString forwarderEmail,
                              QString driverEmail, QString consigneeName, QString consigneeNumber,
                              double finalBid, double finalDriverPrice, QString state, QString bids){
    QSqlQuery query2;
    query2.prepare("UPDATE OrderContract SET orderId = ?, shipperEmail = ?, forwarderEmail = ?, driverEmail = ?, consigneeName = ?, "
                   "consigneeNumber = ?, finalBid = ?, finalDriverPrice = ?, state = ?, bids = ? "
                   "WHERE contractId = ?");
    query2.bindValue(0, orderId);
    query2.bindValue(1, shipperEmail);
    query2.bindValue(2, forwarderEmail);
    query2.bindValue(3, driverEmail);
    query2.bindValue(4, consigneeName);
    query2.bindValue(5, consigneeNumber);
    query2.bindValue(6, finalBid);
    query2.bindValue(7, finalDriverPrice);
    query2.bindValue(8, state);
    query2.bindValue(9, bids);
    query2.bindValue(10, contractId);
    if(query2.exec()){
        qDebug() << "OrderContract table updated";
        return true;
    }
    else{
        qDebug() << "Error = " << query2.lastError().text();
        return false;
    }
}

/*
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
    QDateTime &orderCreated;
};
*/

OrderData database::selectOrderTable(int orderId){
    OrderData thisOrderData;
    QSqlQuery query1;
    query1.prepare("SELECT orderId, sourceAddress, destAddress, sourcePostcode, destPostcode, width, "
                   "height, depth, weight, fragile, description, otherDetails, orderCreated FROM Order WHERE orderId = ?");
    query1.bindValue(0, orderId);
    if(!query1.exec()){
        qDebug() << "Error = " << query1.lastError().text();
    }
    else {
        query1.next();
        thisOrderData.orderId = query1.value(0).toInt();
        thisOrderData.sourceAddress = query1.value(1).toString();
        thisOrderData.destAddress = query1.value(2).toString();
        thisOrderData.sourcePostcode = query1.value(3).toString();
        thisOrderData.destPostcode = query1.value(4).toString();
        thisOrderData.width = query1.value(5).toInt();
        thisOrderData.height = query1.value(6).toInt();
        thisOrderData.depth = query1.value(7).toInt();
        thisOrderData.weight = query1.value(8).toInt();
        thisOrderData.fragile = query1.value(9).toBool();
        thisOrderData.description = query1.value(10).toString();
        thisOrderData.otherDetails = query1.value(11).toString();
        //thisOrderData.orderCreated() = query1.value(12).toDateTime();
        //return thisUserType;
    }
    //return "";
}

/*
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
*/

OrderContractData database::selectOrderContractTable(QString contractId){
    OrderContractData thisOrderContarct;
    QSqlQuery query1;
    query1.prepare("SELECT contractId, orderId, shipperEmail, forwarderEmail, driverEmail, consigneeName, "
                   "consigneeNumber, finalBid, finalDriverPrice, state, bids FROM OrderContract WHERE contractId = ?");
    query1.bindValue(0, contractId);
    if(!query1.exec()){
        qDebug() << "Error = " << query1.lastError().text();
    }
    else {
        query1.next();
        thisOrderContarct.contractId = query1.value(0).toString();
        thisOrderContarct.orderId = query1.value(1).toInt();
        thisOrderContarct.shipperEmail = query1.value(2).toString();
        thisOrderContarct.forwarderEmail = query1.value(3).toString();
        thisOrderContarct.driverEmail = query1.value(4).toString();
        thisOrderContarct.consigneeName = query1.value(5).toString();
        thisOrderContarct.consigneeNumber = query1.value(6).toString();
        thisOrderContarct.finalBid = query1.value(7).toDouble();
        thisOrderContarct.finalDriverPrice = query1.value(8).toDouble();
        thisOrderContarct.state = query1.value(9).toString();
        thisOrderContarct.bids = query1.value(10).toString();
        //return thisUserType;
    }
    //return "";
}


bool database::createInvoiceTable(){
    bool ok;
    QSqlQuery query1;
    if(query1.exec("CREATE TABLE Invoice(invoiceId INT, shipperName TEXT, "
                   "forwarderName TEXT, shipperEmail TEXT, forwarderEmail TEXT, "
                   "date DATETIME, dueDate DATETIME, price INT)")){
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

QString database::getUserValueByEmail(const QString &tableColumnName, const QString &email)
{
    QSqlQuery query;
    query.prepare("SELECT " + tableColumnName + " FROM User WHERE Email = ?");
    query.bindValue(0, email);

    if(!query.exec())
        qDebug() << "Error = " << query.lastError().text();

    if(query.next())
    {
        return query.value(0).toString();
    }
    else
    {
        return "";
    }
}


