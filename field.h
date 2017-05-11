#ifndef GFIELD_H
#define GFIELD_H

#include "yinyen.h"

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
    void checkAdjacent(int x, int y, int &res, int &number);
    void mapInit();
    void mapClear();
    void drawInterface();

private:
    unsigned int xsize;
    unsigned int ysize;
    unsigned int xscreen;
    unsigned int yscreen;
    YinYen ***map;
    RenderWindow *window;
    bool isPlaying;
};

#endif