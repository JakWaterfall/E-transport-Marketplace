#ifndef USER_H
#define USER_H

#include <QObject>
#include <QVector>

class User
{
public:
    User(QString name, QString email, QString password, QString address);
   ~User();

public:
    const QString& getName();
    const QString& getEmail();
    const QString& getPassword();
    const QString& getAddress();
    const QVector<QString> getOrderIDs();
    void insertOrderID(QString ID);
    void removeOrderID(const QString& ID);

protected:
    QString name;
    QString email;
    QString password; // ?? change this to only be in database ? encypted
    QString address;

    QVector<QString> ordersIDs; // just the one?
    //QVector<QString> completedOrdersIDs;
};

#endif // USER_H
