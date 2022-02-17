#ifndef PAGE_H
#define PAGE_H

#include <QWidget>
#include <QListWidgetItem>

#include "clientbroker.h"
#include "ordercontract.h"

class Page : public QWidget
{
    Q_OBJECT
public:
    explicit Page(ClientBroker* broker, QWidget *parent = nullptr);

protected:
    void buildListWidget(QListWidget * list, const QMap<QString, OrderContract*> &contracts);
    void addToListWidget(QListWidget * list, const QString& name, const QString& ID);

private slots:
    void onErrorOccurred(const QString &message);

signals:

protected:
    ClientBroker* broker;
};

#endif // PAGE_H
