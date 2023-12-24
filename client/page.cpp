#include "page.h"

Page::Page(ClientBroker *broker, QWidget *parent) : QWidget(parent), broker(broker)
{
    postcodeToPoint = {{"TR", {5,1}}, {"PL", {7,2}}, {"TQ", {8,2}}, {"EX", {8,3}}, {"TA", {9.5f,3.5f}}, {"DT", {10.5f,2.5f}}, {"BA", {11,4}}, {"BS", {10.5f,4.5f}},
                      {"BH", {11.5f,2.5f}}, {"SP", {12,3.5f}}, {"SN", {12,5}}, {"SO", {13,3}}, {"PO", {13.5f,2.5f}}, {"BN", {15.5,3}}, {"RG", {13,4.5f}}, {"GU", {14,3.5f}},
                      {"RH", {15,3.5f}}, {"TN", {16.5,3.5}}, {"ME", {17,4.5f}}, {"CT", {18,4}}, {"SL", {14,4.5f}}, {"HP", {14,5.5f}}, {"LU", {14.5f,6}}, {"AL", {15,5.5f}},
                      {"SG", {15.5f,6.5f}}, {"CM", {16.5,6}}, {"SS", {17,5}}, {"CO", {17.5f,6}}, {"LONDON", {15.5f,5}}, {"CB", {16,7}}, {"IP", {18,7}}, {"NR", {18,9}},
                      {"HR", {10,7}}, {"GL", {11.5f,6}}, {"OX", {13,6}}, {"MK", {14.5f,6.5f}}, {"PE", {15.5f,8.5f}}, {"WR", {11,7}}, {"NN", {14,7.5f}}, {"LE", {13.5f,8.5f}},
                      {"CV", {12.5f,7.5f}}, {"B", {12,8}}, {"DY", {11,7.5f}}, {"WV", {11,8}}, {"WS", {11.5f,8.5f}}, {"TF", {10.5f,8.5f}}, {"ST", {11.5f,9.5f}}, {"DE", {12.5f,9.5f}},
                      {"NG", {13.5f,9.5f}}, {"LN", {15,10.5f}}, {"S", {12.5f,11}}, {"DN", {14,11}}, {"HU", {15,12}}, {"YO", {14,13}}, {"DL", {12,14.5f}}, {"CA", {10,15}}, {"NE", {12,17}}};
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

float Page::getShippingRate(const QString &sourcePostcode, const QString &destPostcode)
{
    QVector2D source = postcodeToPoint[sourcePostcode];
    QVector2D destination = postcodeToPoint[destPostcode];
    return source.distanceToPoint(destination);
}
