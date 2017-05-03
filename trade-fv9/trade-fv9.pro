TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../src/forv9_trade.cpp \
    ../src/forv9_trade_Demo.cpp \
    ../src/SimpleEvent.cpp

unix:!macx: LIBS += -L$$PWD/../for_v9/lib/ -liTapTradeAPI-fv9

INCLUDEPATH += $$PWD/../for_v9/include
DEPENDPATH += $$PWD/../for_v9/include

HEADERS += \
    ../src/forv9_Trade.h \
    ../src/forv9_TradeConfig.h \
    ../src/SimpleEvent.h
