#include "page.h"

Page::Page(QWidget *parent) : QWidget(parent)
{
    connect(&broker, &Broker::errorOccurred, this, &Page::onErrorOccurred);
}

void Page::onErrorOccurred(const QString &message)
{
    QMessageBox::critical(this, QLatin1String("Error"), message);
}

void Page::buildListWidget(QListWidget * list, const QMap<QString, OrderContract *> &contracts)
{
    list->clear();
    for (auto& contract : contracts)
    {
        //QListWidgetItem* item = new QListWidgetItem(contract->getSellerName() + " " + contract->getSellerEmail(), list);
        //item->setData(Qt::UserRole, contract->getOrder()->getID());
    }
    list->sortItems();
}
