#ifndef CLIENTBROKER_H
#define CLIENTBROKER_H

#include <QObject>
#include <QHostAddress>
#include <broker.h>

class ClientBroker : public Broker
{
    Q_OBJECT
public:
    explicit ClientBroker(QObject *parent = nullptr);

    void logInAttempt(const QString& email, const QString& password);
    void registerAttempt(const QString& name, const QString& email, const QString& password, const QString& confirmPassword, const QString& address, const QString& postcode, const QString &userType);

    void sendOrderToMarketplace(const OrderContract& orderContract);
    void makeBidOnOrder(const QString& orderID, const OrderContract::Bid& bid);
    void sendAcceptBidMessage(const QString& orderID, OrderContract::Bid& bid);
    void acceptJob(const QString& orderID);
    void updateDeliveryState(const QString& orderID, const OrderContract::DeliveryState &deliveryState);
    void requestOrderContracts();
    void requestMarket();

private:
    bool readBody(QDataStream& inStream) override;
    bool processPageSignIn(QDataStream& inStream);
    bool processOrderContracts(QDataStream& inStream, void(ClientBroker::*func)(QMap<QString, OrderContract>&));
    bool processNewMessage(QDataStream& inStream, void(ClientBroker::*func)(const QString&));

private slots:

signals:
    void signInToPage(const QString& pageName);
    void receivedErrorMessage(const QString& errorMessage);
    void receivedMessage(const QString& message);
    void ordersReceived(QMap<QString, OrderContract>& orderContracts);
    void marketReceived(QMap<QString, OrderContract>& marketOrders);

private:

};

#endif // CLIENTBROKER_H
