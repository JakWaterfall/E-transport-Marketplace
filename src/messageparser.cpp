#include "messageparser.h"

MessageParser::MessageParser(QObject *parent) : QObject(parent)
{
    // change all string indexs to consts so they are only changed in one place
}

const QByteArray MessageParser::orderContractToJSON(const OrderContract *contract) const
{
    QJsonObject orderObject = orderToJSONObject(contract->getOrder());

    QJsonObject contractObject;
    contractObject["header"] = "newOrder";
    contractObject["ID"] = contract->getID();
    contractObject["order"] = orderObject;

    return QJsonDocument(contractObject).toJson();
}

OrderContract * MessageParser::orderContractFromJSON(const QJsonDocument &orderContractJSON) const
{
    return new OrderContract(orderFromJSONObject(orderContractJSON["order"].toObject()),
                                                    orderContractJSON["ID"].toString());
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

std::tuple<QString, QString> MessageParser::getLogInFromJSON(QJsonDocument messageJSON)
{
    QString email = messageJSON["email"].toString();
    QString password = messageJSON["password"].toString();
    return  {email, password};
}

const QByteArray MessageParser::pageSignInToJSON(const QString pageName) const
{
    QJsonObject pageSignIn;
    pageSignIn["header"] = "pageSignIn";
    pageSignIn["pageName"] = pageName;

    return QJsonDocument(pageSignIn).toJson();
}

const QByteArray MessageParser::headerMessageToJSON(const QString headerMessage) const
{
    QJsonObject headerJSON;
    headerJSON["header"] = headerMessage;

    return QJsonDocument(headerJSON).toJson();
}

const QByteArray MessageParser::orderDetailsToJSON(const QString header, const QString name, const QString ID) const
{
    QJsonObject orderDetailsJSON;
    orderDetailsJSON["header"] = header;
    orderDetailsJSON["name"] = name;
    orderDetailsJSON["ID"] = ID;

    return QJsonDocument(orderDetailsJSON).toJson();
}

std::tuple<QString, QString> MessageParser::orderDetailsFromJSON(QJsonDocument &messageJSON)
{
    QString name = messageJSON["name"].toString();
    QString ID = messageJSON["ID"].toString();
    return  {name, ID};
}


