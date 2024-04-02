QT += core gui
QT += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arriwal.cpp \
    auth.cpp \
    main.cpp \
    mainwindow.cpp \
    tabprod.cpp

HEADERS += \
    arriwal.h \
    auth.h \
    mainwindow.h \
    tabprod.h

FORMS += \
    arriwal.ui \
    auth.ui \
    mainwindow.ui \
    tabprod.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
