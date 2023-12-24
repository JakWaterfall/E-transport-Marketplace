#ifndef CLIENTBROKER_H
#define CLIENTBROKER_H

#include <QObject>
#include <QHostAddress>
#include <common/broker.h>

/**
 * @brief The ClientBroker class holds all the logic to send messages back and forth with the server.
 */
class ClientBroker : public Broker
{
    Q_OBJECT
public:
    /**
     * @brief ClientBroker constructor
     * @param parent The parent object for QT Framework.
     */
    explicit ClientBroker(QObject *parent = nullptr);

    /**
     * @brief Sends a login attempt to the server.
     * @param email The email of the user trying to login.
     * @param password The password of the user trying to login.
     */
    void logInAttempt(const QString& email, const QString& password);

    /**
     * @brief Sends a register attempt to the server.
     * @param name The name of the user trying to register.
     * @param email The emails of the user trying to register.
     * @param password The password of the user trying to register.
     * @param confirmPassword The password to match with.
     * @param address The address of the user trying to register.
     * @param postcode The postcode of the user trying to register.
     * @param userType The user type (shipper, forwarder or driver) of the user.
     */
    void registerAttempt(const QString& name, const QString& email, const QString& password, const QString& confirmPassword, const QString& address, const QString& postcode, const QString &userType);

    /**
     * @brief Sends a new order to market.
     * @param orderContract The order the user is sending to the marketplace.
     */
    void sendOrderToMarketplace(const OrderContract& orderContract);

    /**
     * @brief Makes a bid on an order.
     * @param orderID The ID of the order to be bidded on.
     * @param bid The bid to be sent.
     */
    void makeBidOnOrder(const QString& orderID, const OrderContract::Bid& bid);

    /**
     * @brief Accepts a bid on an order.
     * @param orderID The ID of the order of the bid.
     * @param bid The bid to be accepted.
     */
    void sendAcceptBidMessage(const QString& orderID, OrderContract::Bid& bid);

    /**
     * @brief Accepts a job for a order.
     * @param orderID The order ID for the job you are accepting.
     */
    void acceptJob(const QString& orderID);

    /**
     * @brief Updates the delivery state of an order.
     * @param orderID The ID of the order.
     * @param deliveryState The new delivery state.
     */
    void updateDeliveryState(const QString& orderID, const OrderContract::DeliveryState &deliveryState);

    /**
     * @brief Sends a request for all the users associated order contracts.
     */
    void requestOrderContracts();

    /**
     * @brief Sends a request for all the orders in the marketplace.
     */
    void requestMarket();

private:
    /**
     * @brief Reads and processes the body of the message based on the header.
     * @param inStream The datastream of the socket for incoming messages.
     * @return True if the message was successfully read.
     */
    bool readBody(QDataStream& inStream) override;

    /**
     * @brief Processes a page sign in message and emits it.
     * @param inStream The datastream of the socket for incoming messages.
     * @return True if the message was successfully read.
     */
    bool processPageSignIn(QDataStream& inStream);

    /**
     * @brief Processes a order contract message and emits it.
     * @param inStream The datastream of the socket for incoming messages.
     * @param func The function pointer to the signal to be emitted after the message was successfully read.
     * @return True if the message was successfully read.
     */
    bool processOrderContracts(QDataStream& inStream, void(ClientBroker::*func)(QMap<QString, OrderContract>&));

    /**
     * @brief Processes a new message(error or normal) message and emits it.
     * @param inStream The datastream of the socket for incoming messages.
     * @param func The function pointer to the signal to be emitted after the message was successfully read.
     * @return True if the message was successfully read.
     */
    bool processNewMessage(QDataStream& inStream, void(ClientBroker::*func)(const QString&));

private slots:

signals:
    /**
     * @brief Emits a sign into page instruction.
     * @param pageName The name of the page to be signed into.
     */
    void signInToPage(const QString& pageName);

    /**
     * @brief Emits an error message.
     * @param errorMessage The error message.
     */
    void receivedErrorMessage(const QString& errorMessage);

    /**
     * @brief Emits a normal message.
     * @param message The message.
     */
    void receivedMessage(const QString& message);

    /**
     * @brief Emits the user related order contracts that have been received.
     * @param orderContracts The order contracts.
     */
    void ordersReceived(QMap<QString, OrderContract>& orderContracts);

    /**
     * @brief Emits the order contracts from the markeplace received.
     * @param marketOrders The orders from the marketplace.
     */
    void marketReceived(QMap<QString, OrderContract>& marketOrders);

};

#endif // CLIENTBROKER_H
