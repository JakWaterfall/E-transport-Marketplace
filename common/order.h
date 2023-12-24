#ifndef ORDER_H
#define ORDER_H

#include <QDateTime>
#include <QDataStream>
#include <QDebug>

/**
 * @brief The Order class which stores order infomation.
 */
class Order
{

public:
    /**
     * @brief Default Order Constructor
     */
    Order();
    /**
     * @brief Order Constuctor
     * @param description The description of the order.
     * @param source The source address of the order.
     * @param destination The destination address of the order.
     * @param sourcePostcode The source postcode of the order.
     * @param destinationPostcode The destination postcode of the order.
     * @param otherDetails Any other details provided of the order.
     * @param width The width of the order in cm.
     * @param height The height of the order in cm.
     * @param depth The depth of the order in cm.
     * @param weight The weight of the order in KG.
     * @param fragile Is the order fragile.
     * @param _orderCreated The time and date the order was created.
     */
    Order(QString description, QString source, QString destination, QString sourcePostcode, QString destinationPostcode, QString otherDetails,
          int width, int height, int depth, int weight, bool fragile, QDateTime _orderCreated = QDateTime::currentDateTimeUtc());

public:
    /**
     * @brief Returns the source address of the order.
     * @return The source address.
     */
    const QString& getSourceAddress() const;

    /**
     * @brief Returns the destination address of the order.
     * @return The destination address.
     */
    const QString& getDestinationAddress() const;

    /**
     * @brief Returns the source postcode of the order.
     * @return The source postcode.
     */
    const QString& getSourcePostcode() const;

    /**
     * @brief Returns the destination postcode of the order.
     * @return The destination postcode.
     */
    const QString& getDestinationPostcode() const;

    /**
     * @brief Returns the description of the order.
     * @return The order description.
     */
    const QString& getDescription() const;

    /**
     * @brief Returns any other details of the order.
     * @return Other details of the order.
     */
    const QString& getOtherDetails() const;

    /**
     * @brief Returns the width of the order.
     * @return The orders width.
     */
    int getWidth() const;

    /**
     * @brief Returns the height of the order.
     * @return The orders height.
     */
    int getHeight() const;

    /**
     * @brief Returns the depth of the order.
     * @return The orders depth.
     */
    int getDepth() const;

    /**
     * @brief Returns the weight of the order.
     * @return The orders weight.
     */
    int getWeight() const;

    /**
     * @brief Returns if the order is fragile.
     * @return True if the order is fragile.
     */
    bool isFragile() const;

    /**
     * @brief Returns the date of the order creation.
     * @return The data the order was made.
     */
    const QDateTime& getCreationDate() const;

    /**
     * @brief Serializes and places an order contact into a datastream.
     * @param stream The datastream the data is to be put into.
     * @param order The order to be serialized.
     * @return The datastream.
     */
    friend QDataStream &operator<< (QDataStream& stream, const Order &order);

    /**
     * @brief Places serialized data into a order contact object from a datastream.
     * @param stream The datastream the data is coming from.
     * @param order The order object to be populated with data.
     * @return The datastream.
     */
    friend QDataStream &operator>> (QDataStream& stream, Order &order);

    /**
     * @brief Places serialized data into this object from a datastream.
     * @param stream The datastream the data is coming from.
     * @return The datastream.
     */
    QDataStream & read(QDataStream & stream);

    /**
     * @brief Serializes and places this order into a datastream.
     * @param stream The datastream the data is to be put into.
     * @return The datastream.
     */
    QDataStream & write(QDataStream & stream) const;

    friend QDebug operator<<(QDebug debug, const Order& order)
    {
        debug << order.getDescription() << order.getCreationDate();
        return debug;
    }


private:
    QString sourceAddress;
    QString destinationAddress;
    QString sourcePostcode;
    QString destinationPostcode;
    int width;
    int height;
    int depth;
    int weight;
    bool fragile;
    QString description;
    QString otherDetails;
    QDateTime orderCreated;
};

#endif // ORDER_H
