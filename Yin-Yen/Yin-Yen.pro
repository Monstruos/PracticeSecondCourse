#-------------------------------------------------
#
# Project created by QtCreator 2017-04-21T16:45:59
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Yin-Yen
TEMPLATE = app

LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

SOURCES += main.cpp \
    field.cpp \
    yinyen.cpp

HEADERS  += \
    field.h \
    yinyen.h

FORMS    +=
