#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include "database.h"
#include "serverbroker.h"
#include "threadsafemap.h"

/**
 * @brief The Controller class that acts as an interface for other types of contollers.
 */
class Controller : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Controller constructor
     * @param broker The Message broker for the server.
     * @param marketplace The marketplace of orders.
     * @param parent The parent object for QT Framework.
     */
    explicit Controller(ServerBroker* broker, ThreadSafeMap<QString, OrderContract *> *marketplace, QObject *parent = nullptr);

signals:

protected:
    /**
     * @brief Saves a vector of order IDs into the database in the format of a CSV file.
     * @param email The email of the user the order IDs are associated with.
     * @param orderIds The order Ids to be saved.
     */
    void saveOrderIdsToDatabase(const QString& email, const QVector<QString> orderIds);

protected:
    ServerBroker* broker;
    ThreadSafeMap<QString, OrderContract *> *marketplace;
};

#endif // CONTEXT_H
