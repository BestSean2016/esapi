TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../src/inv9_Quote.cpp \
    ../src/inv9_TapQuoteDemo.cpp \
    ../src/SimpleEvent.cpp

unix:!macx: LIBS += -L$$PWD/../Inner_v9/lib/ -lTapQuoteAPI-inv9

INCLUDEPATH += $$PWD/../Inner_v9/include
DEPENDPATH += $$PWD/../Inner_v9/include

HEADERS += \
    ../src/inv9_Quote.h \
    ../src/inv9_QuoteConfig.h \
    ../src/SimpleEvent.h
