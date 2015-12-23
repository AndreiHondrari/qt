QT += core
QT -= gui

CONFIG += c++11

TARGET = MultiThreadedReading
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    bigfiledatatransfer.cpp \
    filereadtask.cpp

HEADERS += \
    bigfiledatatransfer.h \
    filereadtask.h
