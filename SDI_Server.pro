QT +=  network
QT += sql
QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

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
    server/database.cpp \
    server/driver.cpp \
    server/drivercontroller.cpp \
    server/forwardercontroller.cpp \
    server/accountmanager.cpp \
    server/connection.cpp \
    server/controller.cpp \
    server/serverbroker.cpp \
    common/broker.cpp \
    server/forwarder.cpp \
    common/order.cpp \
    common/ordercontract.cpp \
    server/server.cpp \
    server/main_server.cpp \
    server/shipper.cpp \
    server/shippercontroller.cpp \
    server/user.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    server/database.h \
    server/driver.h \
    server/drivercontroller.h \
    server/forwardercontroller.h \
    server/accountmanager.h \
    server/connection.h \
    common/broker.h \
    server/controller.h \
    server/forwarder.h \
    common/order.h \
    common/ordercontract.h \
    server/server.h \
    server/shipper.h \
    server/shippercontroller.h \
    server/user.h \
    server/serverbroker.h \
    server/threadsafemap.h
