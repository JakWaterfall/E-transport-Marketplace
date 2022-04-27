#ifndef ORDERCONTRACT_H
#define ORDERCONTRACT_H

#include <QVector>
#include <QUuid>
#include <QDebug>

#include "order.h"

/**
 * @brief The OrderContract class which stores order infomation.
 */
class OrderContract
{

public:
    enum class State {onMarket, inForwarderInventory, inDriverInventory};
    enum class DeliveryState {notApplicable, inTransit, atDepot, outForDelivery, failedToDeliver, successfullyDelivered};
    const static QMap<State, QString> stateToString;
    const static QMap<DeliveryState, QString> DeliveryStateToString;

    /**
     * @brief The Bid struct holds infomation of bids of an order.
     */
    struct Bid
    {
        QString optionalExtras;
        double amount;
        double driverPrice;
        QString forwarderEmail;

        /**
         * @brief Serializes and places Bids into a datastream.
         * @param stream The datastream the data is to be put into.
         * @param bid The bid to be serialized.
         * @return The datastream.
         */
        friend QDataStream &operator<< (QDataStream& stream, const Bid &bid)
        {
            return stream << bid.forwarderEmail << bid.amount << bid.optionalExtras << bid.driverPrice;
        }

        /**
         * @brief Places serialized data into a bid object from a datastream.
         * @param stream The datastream the data is coming from.
         * @param bid The bid object to be populated with data.
         * @return The datastream.
         */
        friend QDataStream &operator>> (QDataStream& stream, Bid &bid)
        {
            return stream >> bid.forwarderEmail >> bid.amount >> bid.optionalExtras >> bid.driverPrice;
        }
    };

public:
    /**
     * @brief Default OrderContract Constructor
     */
    OrderContract();

    /**
     * @brief OrderContract Constructor.
     * @param order The details of the order.
     * @param consigneeName The name of the consignee.
     * @param consigneeNumber The number of the consignee.
     * @param _ID The unique identifier of the order.
     * @param state The current state of the order.
     * @param deliveryState The current delivery state of the order.
     */
    explicit OrderContract(Order order, QString consigneeName, QString consigneeNumber, QString _ID = nullptr,
                           State state = State::onMarket, DeliveryState deliveryState = DeliveryState::notApplicable);
    ~OrderContract();

    /**
     * @brief Returns the orders ID.
     * @return The ID
     */
    const QString& getID() const;

    /**
     * @brief Returns the order object of the contract.
     * @return The order object.
     */
    const Order& getOrder() const;

    /**
     * @brief Returns the shippers email that is associated with the order.
     * @return The shippers email.
     */
    const QString& getShipperEmail() const;

    /**
     * @brief Returns the forwarders email that is associated with the order.
     * @return The forwarders email.
     */
    const QString& getForwarderEmail() const;

    /**
     * @brief Returns the drivers email that is associated with the order.
     * @return The drivers email.
     */
    const QString& getDriverEmail() const;

    /**
     * @brief Returns the name of the consignee of the order.
     * @return The name of the consignee.
     */
    const QString& getConsigneeName() const;

    /**
     * @brief Returns the contact number of the consignee of the order.
     * @return The contact number of the consignee.
     */
    const QString& getConsigneeNumber() const;

    /**
     * @brief Returns the final agreed upon bid amount of the order.
     * @return The final bid amount.
     */
    double getFinalBid() const;

    /**
     * @brief Returns the final agreed upon driver salery of the order.
     * @return The final driver price.
     */
    double getFinalDriverPrice() const;

    /**
     * @brief Returns the state of the order.
     * @return The orders state.
     */
    State getState() const;

    /**
     * @brief Returns the delivery state of the order.
     * @return The orders delivery state.
     */
    DeliveryState getDeliveryState() const;

    /**
     * @brief Returns all the bids the order currently has.
     * @return The bids on an order.
     */
    const QVector<Bid> getBids() const;

    /**
     * @brief Sets the shippers email that will be associated with the order.
     * @param email The shippers email.
     */
    void setShipperEmail(const QString email);

    /**
     * @brief Sets the forwarders email that will be associated with the order.
     * @param email The forwarders email.
     */
    void setForwarderEmail(const QString email);

    /**
     * @brief Sets the drivers email that will be associated with the order.
     * @param email The drivers email.
     */
    void setDriverEmail(const QString email);

    /**
     * @brief Sets the final agreed upon price of the order.
     * @param amount The final price.
     */
    void setFinalBid(const double amount);

    /**
     * @brief Sets the final agreed upon salery of the driver for the order.
     * @param amount The salery of the driver.
     */
    void setFinalDriverPrice(const double amount);

    /**
     * @brief Adds a bid to the order.
     * @param bid The bid to be added.
     */
    void makeBid(Bid bid);

    /**
     * @brief Sets the state of the order.
     * @param _state The new state of the order.
     */
    void setState(State _state);

    /**
     * @brief Sets the delivery state of the order.
     * @param state The new delivery state.
     */
    void setDelveryState(DeliveryState state);

    /**
     * @brief Clears the order of all bids.
     */
    void clearBids();

    /**
     * @brief Checks if a user has already bidded on an order by email.
     * @param email The email of the user to be checked.
     * @return True if the user has already bidded on the order.
     */
    bool hasBidded(const QString& email);

    /**
     * @brief Removes all bids from an order expect for one bid that matches an email.
     * @param email The email of the bid to keep in the order.
     */
    void removeAllOtherBids(const QString& email);

    /**
     * @brief Serializes and places an order contact into a datastream.
     * @param stream The datastream the data is to be put into.
     * @param orderContract The order contact to be serialized.
     * @return The datastream.
     */
    friend QDataStream &operator<< (QDataStream& stream, const OrderContract &orderContract);

    /**
     * @brief Places serialized data into a order contact object from a datastream.
     * @param stream The datastream the data is coming from.
     * @param orderContract The order contract object to be populated with data.
     * @return The datastream.
     */
    friend QDataStream &operator>> (QDataStream& stream, OrderContract &orderContract);

    /**
     * @brief Places serialized data into this object from a datastream.
     * @param stream The datastream the data is coming from.
     * @return The datastream.
     */
    QDataStream & read(QDataStream & stream);

    /**
     * @brief Serializes and places this order contact into a datastream.
     * @param stream The datastream the data is to be put into.
     * @return The datastream.
     */
    QDataStream & write(QDataStream & stream) const;

    /**
     * @brief Serializes and places an delivery state into a datastream.
     * @param stream The datastream the data is to be put into.
     * @param state The delivery state to be serialized.
     * @return The datastream.
     */
    friend QDataStream &operator<< (QDataStream& stream, const OrderContract::DeliveryState & state);

    /**
     * @brief Places serialized state into object from a datastream.
     * @param stream The datastream the data is coming from.
     * @param state The delivery state.
     * @return
     */
    friend QDataStream &operator>> (QDataStream& stream, OrderContract::DeliveryState & state);

    friend QDebug operator<<(QDebug debug, const OrderContract& contract)
    {
        debug << contract.getID() << contract.getOrder();
        return debug;
    }

private:
    QString ID;
    Order order;
    QString shipperEmail;
    QString forwarderEmail;
    QString driverEmail;
    QString consigneeName;
    QString consigneeNumber;
    double finalBid;
    double finalDriverPrice;
    State state;
    DeliveryState deliveryState;
    QVector<Bid> bids;
};

#endif // ORDERCONTRACT_H
