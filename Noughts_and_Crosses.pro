#-------------------------------------------------
#
# Project created by QtCreator 2019-08-20T13:28:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Noughts_and_Crosses
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    nacmodel.cpp \
    markgraphicitem.cpp

HEADERS  += mainwindow.h \
    nacmodel.h \
    item.h \
    markgraphicitem.h

FORMS    += mainwindow.ui
