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

int Field::next()
{

}

bool Field::isDead(YinYen *cell)
{

}

bool Field::isNew(YinYen *cell)
{

}
