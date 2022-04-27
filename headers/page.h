#ifndef PAGE_H
#define PAGE_H

#include <QWidget>
#include <QListWidgetItem>
#include <QPlainTextEdit>
#include <QSpinBox>
#include <QLineEdit>

#include "clientbroker.h"
#include "ordercontract.h"

/**
 * @brief The Page class that acts as an interface for other types of pages.
 */
class Page : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Page Constructor.
     * @param broker The Message broker for the client.
     * @param parent The parent object for QT Framework.
     */
    explicit Page(ClientBroker* broker, QWidget *parent = nullptr);

protected:
    /**
     * @brief Makes a request from the server to refreash the users related order contracts.
     */
    void refreshOrders();

    /**
     * @brief Makes a request from the server to refreash the marketplace order contracts.
     */
    void refreshMarket();

    /**
     * @brief Adds an item to a List Widget object. This is used to add order contracts to a list that is displayed to the user.
     * @param list The list widget that is to be appended to.
     * @param name The name to be displayed in the list.
     * @param ID The order ID to be stored in the list.
     */
    void addToListWidget(QListWidget * list, const QString& name, const QVariant &ID);

    /**
     * @brief Helper function to clear an assortment of widgets.
     * @param lineEdits The Line Edit widgets to be cleared.
     * @param plainTexts The Plain Text widgets to be cleared.
     * @param spinBoxs The Spinbox widgets to be cleared.
     */
    void clearAssortedWidgets(QVector<QLineEdit*> lineEdits, QVector<QPlainTextEdit*> plainTexts, QVector<QDoubleSpinBox*> spinBoxs);

    /**
     * @brief Returns the shipping rate between 2 postcodes.
     * @param sourcePostcode The source postcode.
     * @param destPostcode The destination postcode.
     * @return The shipping rate in pounds.
     */
    float getShippingRate(const QString& sourcePostcode, const QString& destPostcode);


protected:
    ClientBroker* broker;
    QMap<QString, OrderContract> cashedOrderContracts;
    QMap<QString, OrderContract> cashedMarket;
    QMap<QString, QVector2D> postcodeToPoint;
};

#endif // PAGE_H
