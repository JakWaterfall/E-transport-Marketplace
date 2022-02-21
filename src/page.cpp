#include "page.h"

Page::Page(ClientBroker *broker, QWidget *parent) : QWidget(parent), broker(broker)
{
    //    connect(&broker, &Broker::errorOccurred, this, &Page::onErrorOccurred);
}

void Page::refreshOrders()
{
    broker->requestOrderContracts();
}

void Page::refreshMarket()
{
    broker->requestMarket();
}

void Page::addToListWidget(QListWidget *list, const QString &name, const QVariant &ID)
{
    QListWidgetItem* item = new QListWidgetItem(name, list);
    item->setData(Qt::UserRole, ID);
}

void Page::clearAssortedWidgets(QVector<QLineEdit*> lineEdits, QVector<QPlainTextEdit*> plainTexts, QVector<QDoubleSpinBox*> spinBoxs)
{
    for(auto& lineEdit : lineEdits)
        lineEdit->clear();

    for(auto& plainTextEdit : plainTexts)
        plainTextEdit->clear();

    for(auto& spinBox : spinBoxs)
        spinBox->setValue(0.0);
}
