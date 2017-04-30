#ifndef FIELD_H
#define FIELD_H

#include "yinyen.h"

class Field
{
public:
    Field(int x, int y);
    ~Field();
    int next();
protected:
    bool isDead(YinYen *cell);
    bool isNew(YinYen *cell);
private:
    int xsize;
    int ysize;
    YinYen **map;
};

#endif // FIELD_H
