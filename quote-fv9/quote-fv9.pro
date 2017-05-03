TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../src/forv9_Quote.cpp \
    ../src/forv9_quote_demo.cpp \
    ../src/SimpleEvent.cpp

unix:!macx: LIBS += -L$$PWD/../for_v9/lib/ -lTapQuoteAPI-fv9

INCLUDEPATH += $$PWD/../for_v9/include
DEPENDPATH += $$PWD/../for_v9/include

HEADERS += \
    ../src/forv9_Quote.h \
    ../src/forv9_QuoteConfig.h \
    ../src/SimpleEvent.h
