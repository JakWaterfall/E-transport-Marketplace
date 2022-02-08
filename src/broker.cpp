#include "broker.h"

Broker::Broker(QObject *parent) : QObject(parent)
{
    currentTopics.push_back("OrderMarket/");

    client = new QMqttClient(this);
    client->setPort(1883);
    client->setHostname("broker.hivemq.com");
    client->connectToHost();
    qDebug() << client->state();

    connect(client, &QMqttClient::connected, this, [this](){
        subscribeToTopic("OrderMarket/");
    } );

    connect(client, &QMqttClient::messageReceived, this, &Broker::onMessageRecived);
}

Broker::~Broker()
{
    delete client;
}

const QMqttClient *Broker::getClient()
{
    return client;
}

void Broker::subscribeToTopic(const QString &topic)
{
    auto subscription = client->subscribe(topic);
    if (!subscription) {
        emit(errorOccurred("Could not subscribe to " + topic + " is there a connection?"));
        return;
    }
}

bool Broker::publishPackage(const QString &topic, const QString &package) const
{
    if (client->publish(topic, package.toUtf8()) == -1)
        return false;
    return true;
}

void Broker::sendOrderToMarket(const OrderContract *contract)
{
    //emit(errorOccurred("Could not send order."));
    if (!publishPackage("OrderMarket/", JSONParser.orderContractToJSON(contract)))
        emit(errorOccurred("Could not send order."));
}

void Broker::subscribeToAllCurrentTopics()
{

}

void Broker::onMessageRecived(const QByteArray &message, const QMqttTopicName &topic)
{
    //maybe do isValid()?

    if (topic.name() == "OrderMarket/")
        emit(newOrderContract(JSONParser.orderContractFromJSON(message))); // doing this will parse the message evertime even if its not needed
                                                                           // emit the byte array and if a page wants it they can parse it themselfs
}















