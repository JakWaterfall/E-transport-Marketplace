QT +=  network mqtt
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
    src/accountmanager.cpp \
    src/connection.cpp \
    src/controller.cpp \
    src/serverbroker.cpp \
    src/broker.cpp \
    src/forwarder.cpp \
    src/messageparser.cpp \
    src/order.cpp \
    src/ordercontract.cpp \
    src/server.cpp \
    src/main_server.cpp \
    src/shipper.cpp \
    src/shippercontroller.cpp \
    src/user.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    headers/PersonalDetails.h \
    headers/accountmanager.h \
    headers/connection.h \
    headers/broker.h \
    headers/controller.h \
    headers/forwarder.h \
    headers/messageparser.h \
    headers/order.h \
    headers/ordercontract.h \
    headers/server.h \
    headers/shipper.h \
    headers/shippercontroller.h \
    headers/user.h \
    headers/serverbroker.h \
    threadsafemap.h
