TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

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
