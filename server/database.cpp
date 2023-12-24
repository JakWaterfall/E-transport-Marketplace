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
}

void database::database::insertUserTable(QString name, QString email, QString password, QString address, QString postcode, QString userType)
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

    if(!query2.exec()){
        qDebug() << "Error = " << query2.lastError().text();
    }
}

void database::insertUserOrderIds(const QString &email, const QString &orderIds)
{
    QSqlQuery query2;
    query2.prepare("UPDATE User SET orderIds = ? WHERE Email = ?");
    query2.bindValue(0, orderIds);
    query2.bindValue(1, email);

    if(!query2.exec())
        qDebug() << "Error = " << query2.lastError().text();
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
