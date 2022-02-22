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
    void sendOrderToMarketplace(const OrderContract& orderContract);
    void makeBidOnOrder(const QString& orderID, const OrderContract::Bid& bid);
    void sendAcceptBidMessage(const QString& orderID, OrderContract::Bid& bid);
    void acceptJob(const QString& orderID);
    void requestOrderContracts();
    void requestMarket();

private:
    bool readBody(QDataStream& inStream) override;
    bool processPageSignIn(QDataStream& inStream);
    bool processErrorMessage(QDataStream& inStream);
    bool processOrderContracts(QDataStream& inStream, void(ClientBroker::*func)(QMap<QString, OrderContract>&));

private slots:

signals:
    void signInToPage(const QString& pageName);
    void receivedErrorMessage(const QString& errorMessage);
    void ordersReceived(QMap<QString, OrderContract>& orderContracts);
    void marketReceived(QMap<QString, OrderContract>& marketOrders);

private:

};

#endif // CLIENTBROKER_H
