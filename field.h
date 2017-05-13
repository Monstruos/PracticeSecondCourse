#ifndef GFIELD_H
#define GFIELD_H

#include <SFML/Graphics.hpp>
#include "yinyen.h"

using namespace sf;

class GameField
{
public:
    GameField(unsigned int x = 10, unsigned int y = 10);
    ~GameField();
    void next();
    void show();

protected:
    bool isDead(int x, int y);
    int isNew(int x, int y);
    void checkAdjacent(int x, int y, int *res, int *number);
    void mapInit();
    void mapClear();
    void drawInterface();
    void drawMap();
    void eventHandler(Event event);

private:
    unsigned int xsize;
    unsigned int ysize;
    unsigned int xscreen;
    unsigned int yscreen;
    RectangleShape *back;
    Texture backTxt;
    YinYen ***map;
    YinYen ***nextmap;
    RenderWindow *window;
    bool isPlaying;
    CircleShape *Yin;
    CircleShape *Yen;
    Clock *cl;
    Time elapse;
};

#endif