#include "page.h"

Page::Page(ClientBroker *broker, QWidget *parent) : QWidget(parent), broker(broker)
{
//    connect(&broker, &Broker::errorOccurred, this, &Page::onErrorOccurred);
}

void Page::onErrorOccurred(const QString &message)
{
//    QMessageBox::critical(this, QLatin1String("Error"), message);
}

void Page::buildListWidget(QListWidget * list, const QMap<QString, OrderContract *> &contracts)
{
    list->clear();
    // send message to build whatever list
    for (auto& contract : contracts)
    {
        //QListWidgetItem* item = new QListWidgetItem(contract->getSellerName() + " " + contract->getSellerEmail(), list);
        //item->setData(Qt::UserRole, contract->getOrder()->getID());
    }
    list->sortItems();
}

void Page::addToListWidget(QListWidget *list, const QString &name, const QString &ID)
{
    QListWidgetItem* item = new QListWidgetItem(name, list);
    item->setData(Qt::UserRole, ID);
}
