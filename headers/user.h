#ifndef USER_H
#define USER_H

#include <QObject>

class User
{
public:
    User(QString firstName, QString lastName, QString email, QString password, QString address);
   ~User();

public:
    const QString& getFirstName();
    const QString& getLastName();
    const QString& getEmail();
    const QString& getPassword();
    const QString& getAddress();

protected:
    QString firstName;
    QString lastName;
    QString email;
    QString password; // ?? change this to only be in database ? encypted
    QString address;
};

#endif // USER_H
