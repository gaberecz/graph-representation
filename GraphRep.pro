#-------------------------------------------------
#
# Project created by QtCreator 2014-02-26T09:47:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphRep
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    drawer.cpp \
    graphstructure.cpp

HEADERS  += mainwindow.h \
    drawer.h \
    graphstructure.h

FORMS    += mainwindow.ui
