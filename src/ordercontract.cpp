#include "ordercontract.h"

const QMap<OrderContract::State, QString> OrderContract::stateToString = {{State::onMarket, "On The Market"},
                                                                          {State::inForwarderInventory, "In Forwarders Inventory"},
                                                                          {State::inDriverInventory, "In Drivers Inventory"}};

const QMap<OrderContract::DeliveryState, QString> OrderContract::DeliveryStateToString = {{DeliveryState::notApplicable, "N/A"},
                                                                                          {DeliveryState::atDepot, "At The Depot"},
                                                                                          {DeliveryState::inTransit, "Currently in Transit"},
                                                                                          {DeliveryState::outForDelivery, "Out For Delivery"},
                                                                                          {DeliveryState::failedToDeliver, "Failed To Deliver"}};

OrderContract::OrderContract()
{}

OrderContract::OrderContract(Order order, QString consigneeName, QString consigneeNumber, QString _ID, State state, DeliveryState deliveryState)
    : order(order), consigneeName(consigneeName), consigneeNumber(consigneeNumber), state(state), deliveryState(deliveryState)
{
    if (_ID == nullptr)
    {
        ID = QUuid::createUuid().toString();
    }
    else
    {
        ID = _ID;
    }
    // use UUID for id
}

OrderContract::~OrderContract()
{}

const QString &OrderContract::getID() const
{
    return ID;
}

const Order &OrderContract::getOrder() const
{
    return order;
}

const QString &OrderContract::getShipperEmail() const
{
    return shipperEmail;
}

const QString &OrderContract::getForwarderEmail() const
{
    return forwarderEmail;
}

const QString &OrderContract::getDriverEmail() const
{
    return driverEmail;
}

const QString &OrderContract::getConsigneeName() const
{
    return consigneeName;
}

const QString &OrderContract::getConsigneeNumber() const
{
    return consigneeNumber;
}

double OrderContract::getFinalBid() const
{
    return finalBid;
}

double OrderContract::getFinalDriverPrice() const
{
    return finalDriverPrice;
}

OrderContract::DeliveryState OrderContract::getDeliveryState() const
{
    return deliveryState;
}

const QVector<OrderContract::Bid> OrderContract::getBids() const
{
    return bids;
}

OrderContract::State OrderContract::getState() const
{
    return state;
}

void OrderContract::setShipperEmail(const QString email)
{
    shipperEmail = email;
}

void OrderContract::setForwarderEmail(const QString email)
{
    forwarderEmail = email;
}

void OrderContract::setDriverEmail(const QString email)
{
    driverEmail = email;
}

void OrderContract::setFinalBid(const double amount)
{
    finalBid = amount;
}

void OrderContract::setFinalDriverPrice(const double amount)
{
    finalDriverPrice = amount;
}

void OrderContract::makeBid(Bid bid)
{
    bids.push_back(bid);
}

void OrderContract::setState(OrderContract::State _state)
{
    state = _state;
}

void OrderContract::setDelveryState(OrderContract::DeliveryState state)
{
    deliveryState = state;
}

void OrderContract::clearBids()
{
    bids.clear();
}

bool OrderContract::hasBidded(const QString &email)
{
    for(auto& bid : bids)
    {
        if(bid.forwarderEmail == email)
            return true;
    }
    return false;
}

void OrderContract::removeAllOtherBids(const QString &email)
{
    bids.erase(std::remove_if(std::begin(bids), std::end(bids), [email](OrderContract::Bid& bid)
    {
        return bid.forwarderEmail != email;
    }
    ), std::end(bids));
}

QDataStream & operator<<(QDataStream &stream, const OrderContract &orderContract)
{
    return orderContract.write(stream);
}

QDataStream & operator>>(QDataStream &stream, OrderContract &orderContract)
{
    return orderContract.read(stream);
}

QDataStream &OrderContract::read(QDataStream &stream)
{
    stream >> ID >> order >> shipperEmail >> forwarderEmail >> driverEmail >> consigneeName >> consigneeNumber >> finalBid >> finalDriverPrice >> bids;

    qint32 state_int = 0;
    qint32 deliveryState_int = 0;
    stream >> state_int >> deliveryState_int;

    state = static_cast<State>(state_int);
    deliveryState = static_cast<DeliveryState>(deliveryState_int);
    return stream;
}

QDataStream &OrderContract::write(QDataStream &stream) const
{
    stream << ID << order << shipperEmail << forwarderEmail << driverEmail << consigneeName << consigneeNumber << finalBid << finalDriverPrice << bids;
    stream << static_cast<qint32>(state) << static_cast<qint32>(deliveryState);
    return stream;
}
