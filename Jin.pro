TEMPLATE = app
TARGET = jin
INCLUDEPATH += .

QT += widgets core gui
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += MainWindow.hpp Jin.h
SOURCES += Main.cpp MainWindow.cpp Jin.cpp
QMAKE_CXXFLAGS += -Wno-write-strings
LIBS += -lboost_system -lboost_filesystem