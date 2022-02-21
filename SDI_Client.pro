QT       += core gui network mqtt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += headers/

SOURCES += \
    src/clientbroker.cpp \
    src/broker.cpp \
    src/forwarderpage.cpp \
    src/main_client.cpp \
    src/mainwindow.cpp \
    src/order.cpp \
    src/ordercontract.cpp \
    src/page.cpp \
    src/sellerpage.cpp

HEADERS += \
    headers/clientbroker.h \
    headers/broker.h \
    headers/forwarderpage.h \
    headers/mainwindow.h \
    headers/order.h \
    headers/ordercontract.h \
    headers/page.h \
    headers/sellerpage.h

FORMS += \
    ui/forwarderpage.ui \
    ui/mainwindow.ui \
    ui/sellerpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
