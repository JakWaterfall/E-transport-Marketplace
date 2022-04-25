#ifndef USER_H
#define USER_H

#include <QObject>
#include <QVector>

class User
{
public:
    User(QString name, QString email, QString address, QString postcode, QVector<QString> ordersIDs);
   ~User();

public:
    const QString& getName();
    const QString& getEmail();
    const QString& getAddress();
    const QString &getPostcode();
    const QVector<QString> getOrderIDs();
    void insertOrderID(QString ID);
    void removeOrderID(const QString& ID);

protected:
    QString name;
    QString email;
    QString address;
    QString postcode;

    QVector<QString> ordersIDs;
};

#endif // USER_H
