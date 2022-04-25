#ifndef PAGE_H
#define PAGE_H

#include <QWidget>
#include <QListWidgetItem>
#include <QPlainTextEdit>
#include <QSpinBox>
#include <QLineEdit>

#include "clientbroker.h"
#include "ordercontract.h"

class Page : public QWidget
{
    Q_OBJECT
public:
    explicit Page(ClientBroker* broker, QWidget *parent = nullptr);

protected:
    void refreshOrders();
    void refreshMarket();
    void addToListWidget(QListWidget * list, const QString& name, const QVariant &ID);
    void clearAssortedWidgets(QVector<QLineEdit*> lineEdits, QVector<QPlainTextEdit*> plainTexts, QVector<QDoubleSpinBox*> spinBoxs);
    float getShippingRate(const QString& sourcePostcode, const QString& destPostcode);

private slots:

signals:

protected:
    ClientBroker* broker;
    QMap<QString, OrderContract> cashedOrderContracts;
    QMap<QString, OrderContract> cashedMarket;
    QMap<QString, QVector2D> postcodeToPoint;
};

#endif // PAGE_H
