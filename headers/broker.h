#ifndef BROKER_H
#define BROKER_H

#include <QObject>
#include <QtMqtt/QtMqtt>
#include <QtCore/QDateTime>
#include <QtMqtt/QMqttClient>
#include <QtWidgets/QMessageBox>
#include "order.h"
#include "user.h"
#include "ordercontract.h"
#include "messageparser.h"

class Broker : public QObject
{
    Q_OBJECT

public:
    explicit Broker(QObject *parent = nullptr);
    ~Broker();

    const QMqttClient * getClient();
    void sendOrderToMarket(const OrderContract *contract);
    void subscribeToTopic(const QString &topic);

private:

    bool publishPackage(const QString &topic, const QString &package) const;

private slots:
    void subscribeToAllCurrentTopics();
    void onMessageRecived(const QByteArray &message, const QMqttTopicName &topic);

signals:
    void errorOccurred(const QString &message);
    void newOrderContract(OrderContract *contract);

private:
    QMqttClient *client;
    QVector<QString> currentTopics;
    MessageParser JSONParser;
};

#endif // BROKER_H
