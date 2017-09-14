#-------------------------------------------------
#
# Project created by QtCreator 2017-09-14T09:51:31
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Exam_Kiosk
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    listeningtag.cpp

HEADERS  += mainwindow.h \
    listeningtag.h

FORMS    += mainwindow.ui

RESOURCES += \
    src.qrc
