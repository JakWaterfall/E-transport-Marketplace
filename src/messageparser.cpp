#include "messageparser.h"

MessageParser::MessageParser(QObject *parent) : QObject(parent)
{

}

const QByteArray MessageParser::orderContractToJSON(const OrderContract *contract) const
{
    QJsonObject orderObject = orderToJSONObject(contract->getOrder());
    QJsonObject contractObject;
    contractObject["sellerName"] = contract->getSellerName();
    contractObject["sellerEmail"] = contract->getSellerEmail();
    contractObject["responceTopic"] = contract->getResponceTopic();
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
                                                    doc["sellerName"].toString(),
                                                    doc["sellerEmail"].toString(),
                                                    doc["responceTopic"].toString());
}

QJsonObject MessageParser::orderToJSONObject(const Order *order) const
{
    QJsonObject JSON;
    JSON["ID"] = order->getID();
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
                    QDateTime::fromString(JSONObject["creationDate"].toString()),
                    JSONObject["ID"].toString());
}


