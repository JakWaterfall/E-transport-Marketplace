#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include <QObject>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include "order.h"
#include "ordercontract.h"

class MessageParser : public QObject
{
    Q_OBJECT
public:
    explicit MessageParser(QObject *parent = nullptr);
    const QByteArray orderContractToJSON(const OrderContract* contract) const;
    OrderContract* orderContractFromJSON(const QByteArray &JSON) const;

    QJsonObject orderToJSONObject(const Order* order) const;
    Order* orderFromJSONObject(const QJsonObject &JSONObject) const;

    QJsonDocument toJSONdocument(const QByteArray& message);

    const QByteArray logInAttemptToJSON(const QString email, const QString password);



signals:

public:
    const QString headerStr = "header";
    const QString loginStr = "login";
    const QString newOrderStr = "newOrder";

};

#endif // MESSAGEPARSER_H
