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

    void logInAttempt(QString email, QString password);
    void sendOrderToMarketplace(const OrderContract *orderContract);
    void buildOrderScreen();

private:
    bool readBody(QDataStream& inStream) override;
    bool processPageSignIn(QDataStream& inStream);
    bool processPendingOrders(QDataStream& inStream);

private slots:

signals:
    void logInAsShipper();
    void logInAsForwarder();
    void logInAsDriver();
    void signInToPage(QString pageName);
    void pendingOrderReceived(QVector<OrderContract> orderContracts);

private:

};

#endif // CLIENTBROKER_H
