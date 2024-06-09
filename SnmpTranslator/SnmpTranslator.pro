QT -= gui
QT += network sql

CONFIG += c++17 console
CONFIG -= app_bundle

#INCLUDEPATH += /usr/lib/x86_64-linux-gnu/
#LIBS += /usr/lib/x86_64-linux-gnu/libpq.so.5

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        dblayerbase.cpp \
        main.cpp \
        snmpparse.cpp \
        snmptrapserver.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    dblayerbase.h \
    snmpparse.h \
    snmptrapserver.h
