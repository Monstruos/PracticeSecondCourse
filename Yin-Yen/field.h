#ifndef FIELD_H
#define FIELD_H

#include "yinyen.h"

class Field
{
public:
    Field(int x, int y);
    ~Field();
    void next();
protected:
    bool isDead(int x, int y);
    int isNew(int x, int y);
    void checkAdjacent(int x, int y, int &res, int &number);
private:
    int xsize;
    int ysize;
    YinYen **map;
};

#endif // FIELD_H
