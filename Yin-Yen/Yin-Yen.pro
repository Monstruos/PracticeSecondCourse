TEMPLATE = app
CONFIG -= qt
CONFIG += gui

SOURCES += main.cpp \
field.cpp \
yinyen.cpp \

HEADERS += field.h \
yinyen.h

LIBS += -L"/home/monstruos/SFML_builds/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += "/home/monstruos/SFML-master/include"
DEPENDPATH += "/home/monstruos/SFML-master/include"
