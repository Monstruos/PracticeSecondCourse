#include "field.h"

Field::Field(int x = 10, int y = 10) :
    xsize(x),
    ysize(y)
{
    map = new YinYen* [xsize];
    for(int i = 0; i < xsize; ++i)
        map[i] = new YinYen [ysize];
}

Field::~Field()
{
    for(int i = 0; i < xsize; ++i)
        delete map[i];
    delete map;
}

void Field::next()
{
    YinYen **nextmap;
    nextmap = new YinYen* [xsize];
    for(int i = 0; i < xsize; ++i)
    {
        nextmap[i] = new YinYen [ysize];
        for(int j = 0; j < ysize; ++j)
        {
            int notEmpty = map[i][j].getStatus();
            int New = isNew(i, j);
            if(notEmpty == 0 && New != 0)
                nextmap[i][j].setStatus(New);

            if(notEmpty != 0 && isDead(i, j))
                nextmap[i][j].setStatus(0);
        }
    }
    for(int i = 0; i < xsize; ++i)
        delete map[i];
    delete map;
    map = nextmap;
}

bool Field::isDead(int x, int y)
{
    if(map[x][y].getStatus() == 0)
        return true;

    int res, count;
    checkAdjacent(x, y, res, count);

    if(count < 2 || count > 4)
        return true;

    if(count == 4)
        if((map[x][y].getStatus() * res) < 0)
            return true;

    return false;
}

int Field::isNew(int x, int y)
{
    int res, count;
    checkAdjacent(x, y, res, count);

    if(count == 3)
    {
        if(res == 1)
            return -1;
        if(res == -1)
            return 1;
    }
    return 0;
}

void Field::checkAdjacent(int x, int y, int &res, int &number)
{
    int bufStat;
    res = 0;
    number = 0;
    int K[8][2] = {
        {-1, -1},
        {-1,  0},
        {-1,  1},
        { 0, -1},
        { 0,  1},
        { 1, -1},
        { 1,  0},
        { 1,  1}
    };
    int kx, ky;
    int i;
    for(i = 0; i < 8; ++i)
    {
        kx = x+K[i][0];
        ky = y+K[i][1];
        if(kx >= 0 && ky >= 0 &&
            kx < xsize && ky < ysize)
        {
            bufStat = map[kx][ky].getStatus();
            if(bufStat != 0)
            {
                res += bufStat;
                number++;
            }
        }
    }
}
