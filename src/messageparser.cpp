#include "messageparser.h"

MessageParser::MessageParser(QObject *parent) : QObject(parent)
{
    // change all string indexs to consts so they are only changed in one place
}

const QByteArray MessageParser::orderContractToJSON(const OrderContract *contract) const
{
    QJsonObject orderObject = orderToJSONObject(contract->getOrder());

    QJsonObject contractObject;
    contractObject["ID"] = contract->getID();
    contractObject["sellerEmail"] = contract->getSellerEmail();
    contractObject["order"] = orderObject;

    return QJsonDocument(contractObject).toJson();
}

OrderContract *MessageParser::orderContractFromJSON(const QByteArray& JSON) const
{
    // check if fromJSON worked
    QJsonParseError * errorCode = nullptr;
    QJsonDocument doc = QJsonDocument::fromJson(JSON, errorCode);
    if(doc.isNull())
    {
        // emit failure
        qDebug() << errorCode->errorString();
        return nullptr;
    }
    return new OrderContract(orderFromJSONObject(doc["order"].toObject()),
                                                    doc["sellerEmail"].toString(),
                                                    doc["ID"].toString());
}

QJsonObject MessageParser::orderToJSONObject(const Order *order) const
{
    QJsonObject JSON;
    JSON["type"] = order->getType();
    JSON["weight"] = order->getWeight();
    JSON["dismensions"] = order->getDismensions();
    JSON["creationDate"] = order->getCreationDate().toString();
    JSON["sourceAddress"] = order->getSourceAddress();
    JSON["destinationAddress"] = order->getDestinationAddress();
    JSON["fragile"] = order->isFragile();
    return JSON;
}

Order * MessageParser::orderFromJSONObject(const QJsonObject &JSONObject) const
{
    return new Order(JSONObject["sourceAddress"].toString(),
                    JSONObject["destinationAddress"].toString(),
                    JSONObject["dismensions"].toString(),
                    JSONObject["weight"].toInt(),
                    JSONObject["fragile"].toBool(),
                    JSONObject["type"].toString(),
                    QDateTime::fromString(JSONObject["creationDate"].toString()));
}

QJsonDocument MessageParser::toJSONdocument(const QByteArray &message)
{
    // check if fromJSON worked
    QJsonParseError * errorCode = nullptr;
    QJsonDocument document = QJsonDocument::fromJson(message, errorCode);
    if(document.isNull())
    {
        // emit failure
        qDebug() << errorCode->errorString();
    }
    return document;
}

const QByteArray MessageParser::logInAttemptToJSON(const QString email, const QString password)
{
    QJsonObject logInAttempt;
    logInAttempt["header"] = "login";
    logInAttempt["email"] = email;
    logInAttempt["password"] = password;

    return QJsonDocument(logInAttempt).toJson();
}



