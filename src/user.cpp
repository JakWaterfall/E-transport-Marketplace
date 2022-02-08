#include "user.h"

User::User(QString firstName, QString lastName, QString email, QString password, QString address)
    : firstName(firstName), lastName(lastName), email(email), password(password), address(address)
{

}

User::~User()
{

}

const QString &User::getFirstName()
{
    return firstName;
}

const QString &User::getLastName()
{
    return lastName;
}

const QString &User::getEmail()
{
    return email;
}

const QString &User::getPassword()
{
    return password;
}

const QString &User::getAddress()
{
    return address;
}
