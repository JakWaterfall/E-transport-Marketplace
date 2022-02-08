#ifndef PAGE_H
#define PAGE_H

#include <QWidget>
#include <QListWidgetItem>

#include "broker.h"
#include "ordercontract.h"

class Page : public QWidget
{
    Q_OBJECT
public:
    explicit Page(QWidget *parent = nullptr);

protected:
    void buildListWidget(QListWidget * list, const QMap<QString, OrderContract*> &contracts);

private slots:
    void onErrorOccurred(const QString &message);

signals:

protected:
    Broker broker;
};

#endif // PAGE_H
