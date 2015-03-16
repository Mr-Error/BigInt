#-------------------------------------------------
#
# Project created by QtCreator 2015-02-26T16:14:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BigInt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11 -O3
