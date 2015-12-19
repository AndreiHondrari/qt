#-------------------------------------------------
#
# Project created by QtCreator 2015-12-19T13:17:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RandomNumbers
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    randomnumberswidget.cpp

HEADERS  += mainwindow.h \
    randomnumberswidget.h

FORMS    += mainwindow.ui

CONFIG += c++11
