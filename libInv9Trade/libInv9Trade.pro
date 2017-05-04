c#-------------------------------------------------
#
# Project created by QtCreator 2017-05-04T22:33:35
#
#-------------------------------------------------

QT       -= core gui

TARGET = libInv9Trade
TEMPLATE = lib

DEFINES += LIBINV9TRADE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    ../src/inv9_TapTradeDemo.cpp \
    ../src/inv9_Trade.cpp \
    ../src/SimpleEvent.cpp

unix:!macx: LIBS += -L$$PWD/../Inner_v9/lib/ -lTapTradeAPI-inv9

INCLUDEPATH += $$PWD/../Inner_v9/include
DEPENDPATH += $$PWD/../Inner_v9/include

HEADERS += \
    ../src/inv9_Trade.h \
    ../src/inv9_TradeConfig.h \
    ../src/SimpleEvent.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
