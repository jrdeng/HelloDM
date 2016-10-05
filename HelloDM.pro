#-------------------------------------------------
#
# Project created by QtCreator 2016-10-02T02:24:06
#
#-------------------------------------------------

QT       += core gui axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HelloDM
TEMPLATE = app


SOURCES += main.cpp\
    widget.cpp \
    dmwrapper.cpp

HEADERS  += widget.h \
    dmwrapper.h

FORMS    += widget.ui
