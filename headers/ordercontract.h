#ifndef ORDERCONTRACT_H
#define ORDERCONTRACT_H

#include <QObject>

#include "order.h"

class OrderContract : public QObject
{
    Q_OBJECT

public:
    explicit OrderContract(Order* order, QString sellerName, QString sellerEmail, QString responceTopic, QObject *parent = nullptr);
    ~OrderContract();

    const Order* getOrder() const;
    const QString& getSellerName() const;
    const QString& getSellerEmail() const;
    const QString& getForwarderName() const;
    const QString& getForwarderEmail() const;
    double getForwarderBid() const;
    const QString& getResponceTopic() const;

    void setForwarderName(const QString name);
    void setForwarderEmail(const QString email);
    void setForwarderBid(const double amount);

signals:

private:
    Order* order;
    QString sellerName;
    QString sellerEmail;
    QString forwarderName;
    QString forwarderEmail;
    double forwarderBid;
    QString responceTopic;
    // make details a struct for seller, forwarder, consignee
};

#endif // ORDERCONTRACT_H
