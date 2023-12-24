#ifndef SERVERBROKER_H
#define SERVERBROKER_H

#include <QObject>
#include "common/broker.h"

/**
 * @brief The ServerBroker class holds all the logic to send messages back and forth with the client.
 */
class ServerBroker : public Broker
{
    Q_OBJECT
public:
    /**
     * @brief ServerBroker constructor
     * @param socket The TCP socket that connects client and server.
     * @param parent The parent object for QT Framework.
     */
    explicit ServerBroker(QTcpSocket* socket, QObject *parent = nullptr);

    /**
     * @brief Sends an error message to the client.
     * @param message The message sent.
     */
    void sendErrorMessage(const QString& message);

    /**
     * @brief Sends a normal message to the client.
     * @param message The message sent.
     */
    void sendMessage(const QString& message);

    /**
     * @brief Sends instruction to client to open up the correct user type page. (Shipper, forwarder or driver)
     * @param pageName The name of the page to be opened.
     */
    void sendPageSignIn(const QString& pageName) const;

    /**
     * @brief Sends related order contacts to the client.
     * @param orders The orders to be sent.
     */
    void sendUserRelatedOrderContracts(const QMap<QString, OrderContract> &orders);

    /**
     * @brief Sends the order contacts on the market to the client.
     * @param marketOrders The orders to be sent.
     */
    void sendMarketOrderContracts(const QMap<QString, OrderContract> &marketOrders);

private:
    /**
     * @brief Processes a login message and emits it.
     * @param inStream The datastream of the socket for incoming messages.
     * @return True if the message was successfully read.
     */
    bool processLogIn(QDataStream& inStream);

    /**
     * @brief Processes a register message and emits it.
     * @param inStream The datastream of the socket for incoming messages.
     * @return True if the message was successfully read.
     */
    bool processRegister(QDataStream& inStream);

    /**
     * @brief Processes a new order message and emits it.
     * @param inStream The datastream of the socket for incoming messages.
     * @return True if the message was successfully read.
     */
    bool processNewOrder(QDataStream& inStream);

    /**
     * @brief Processes a new bid message and emits it.
     * @param inStream The datastream of the socket for incoming messages.
     * @return True if the message was successfully read.
     */
    bool processNewBid(QDataStream& inStream);

    /**
     * @brief Processes an accept bid message and emits it.
     * @param inStream The datastream of the socket for incoming messages.
     * @return True if the message was successfully read.
     */
    bool processAcceptBid(QDataStream& inStream);

    /**
     * @brief Processes an accept job message and emits it.
     * @param inStream The datastream of the socket for incoming messages.
     * @return True if the message was successfully read.
     */
    bool processAcceptJob(QDataStream& inStream);

    /**
     * @brief Processes an update delivery state message and emits it.
     * @param inStream The datastream of the socket for incoming messages.
     * @return True if the message was successfully read.
     */
    bool processUpdateDeliveryState(QDataStream& inStream);

    /**
     * @brief Reads and processes the body of the message based on the header.
     * @param inStream The datastream of the socket for incoming messages.
     * @return True if the message was successfully read.
     */
    bool readBody(QDataStream& inStream) override;

    /**
     * @brief Sends order contacts to the client with an accompanying header message.
     * @param header The header message for the order contracts
     * @param orders The order contracts to be sent.
     */
    void sendOrderContracts(const QString& header, const QMap<QString, OrderContract> &orders);

private slots:

signals:
    /**
     * @brief Emits a login attempt.
     * @param email The email of the user.
     * @param password The password of the user.
     */
    void logInAttempt(const QString& email, const QString& password);

    /**
     * @brief Emits a register attempt.
     * @param name The name of the user.
     * @param email The email of the user.
     * @param password The password of the user.
     * @param confirmPass The password to match with.
     * @param address The address of the user.
     * @param postcode The postcode of the user.
     * @param userType The user type (shipper, forwarder or driver) of the user.
     */
    void registerAttempt(const QString& name, const QString& email, const QString& password, const QString& confirmPass, const QString& address, const QString& postcode, const QString& userType);

    /**
     * @brief Emits a new order contract.
     * @param orderContract The order contract.
     */
    void newOrderContract(OrderContract* orderContract);

    /**
     * @brief Emits a new bid on an order instruction.
     * @param orderID The ID of the order involved.
     * @param bid The new bid received.
     */
    void newBidOnOrder(const QString& orderID, OrderContract::Bid& bid);

    /**
     * @brief Emits an accept bid instruction.
     * @param orderID The ID of the order involved.
     * @param bid The bid that has been accepted.
     */
    void acceptBid(const QString& orderID, OrderContract::Bid& bid);

    /**
     * @brief Emits an accept job instruction.
     * @param orderID The ID of the order involved.
     */
    void acceptJob(const QString& orderID);

    /**
     * @brief Emits an update delivery instruction.
     * @param orderID The ID of the order involved.
     * @param deliveryState The new delivery state.
     */
    void updateDeliveryState(const QString& orderID, const OrderContract::DeliveryState &deliveryState);

    /**
     * @brief Emits a request for order contacts.
     */
    void requestForOrderContracts();

    /**
     * @brief Emits a request for market order contacts.
     */
    void requestForMarket();

};

#endif // SERVERBROKER_H
