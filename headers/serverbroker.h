#ifndef SERVERBROKER_H
#define SERVERBROKER_H

#include <QObject>
#include "broker.h"

class ServerBroker : public Broker
{
    Q_OBJECT
public:
    explicit ServerBroker(QTcpSocket* socket, QObject *parent = nullptr);
    void sendErrorMessage(const QString& message);
    void sendMessage(const QString& message);
    void sendPageSignIn(const QString& pageName) const;
    void sendUserRelatedOrderContracts(const QMap<QString, OrderContract> &orders);
    void sendMarketOrderContracts(const QMap<QString, OrderContract> &marketOrders);

private:
    bool processLogIn(QDataStream& inStream);
    bool processRegister(QDataStream& inStream);
    bool processNewOrder(QDataStream& inStream);
    bool processNewBid(QDataStream& inStream);
    bool processAcceptBid(QDataStream& inStream);
    bool processAcceptJob(QDataStream& inStream);
    bool processUpdateDeliveryState(QDataStream& inStream);
    bool readBody(QDataStream& inStream) override;
    void sendOrderContracts(const QString& header, const QMap<QString, OrderContract> &orders);

private slots:

signals:
    void logInAttempt(const QString& email, const QString& password);
    void registerAttempt(const QString& name, const QString& email, const QString& password, const QString& confirmPass, const QString& address, const QString& postcode, const QString& userType);
    void newOrderContract(OrderContract* orderContract);
    void newBidOnOrder(const QString& orderID, OrderContract::Bid& bid);
    void acceptBid(const QString& orderID, OrderContract::Bid& bid);
    void acceptJob(const QString& orderID);
    void updateDeliveryState(const QString& orderID, const OrderContract::DeliveryState &deliveryState);
    void requestForOrderContracts();
    void requestForMarket();

private:

};

#endif // SERVERBROKER_H
