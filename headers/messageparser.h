#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include <QObject>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <tuple>
#include "order.h"
#include "ordercontract.h"

class MessageParser : public QObject
{
    Q_OBJECT
public:
    explicit MessageParser(QObject *parent = nullptr);
    const QByteArray orderContractToJSON(const OrderContract* contract) const;
    OrderContract* orderContractFromJSON(const QJsonDocument &orderContractJSON) const;

    QJsonObject orderToJSONObject(const Order* order) const;
    Order* orderFromJSONObject(const QJsonObject &JSONObject) const;

    QJsonDocument toJSONdocument(const QByteArray& message);

    const QByteArray logInAttemptToJSON(const QString email, const QString password);
    std::tuple<QString, QString> getLogInFromJSON(QJsonDocument messageJSON);

    const QByteArray pageSignInToJSON(const QString pageName) const;

    const QByteArray headerMessageToJSON(const QString headerMessage) const;

    const QByteArray orderDetailsToJSON(const QString header, const QString name, const QString ID) const;

    std::tuple<QString, QString> orderDetailsFromJSON(QJsonDocument& messageJSON);

signals:

public:
    const QString headerStr = "header";
    const QString loginStr = "login";
    const QString newOrderStr = "newOrder";

};

#endif // MESSAGEPARSER_H
