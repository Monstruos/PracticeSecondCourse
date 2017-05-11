#include "yinyen.h"

YinYen::YinYen() :
        xpos(0),
        ypos(0),
        stat(0)
{

}

YinYen::YinYen(unsigned int x, unsigned int y, int status) :
        xpos(x),
        ypos(y)
{
    (status < 2 && status > -2) ? stat = status : stat = 0;
}

YinYen::~YinYen()
{

}

void YinYen::setStatus(int status)
{
    (status < 2 && status > -2) ? stat = status : stat = 0;
}

int YinYen::getStatus()
{
    return stat;
}

void YinYen::getXY(unsigned int &x, unsigned int &y)
{
    x = xpos;
    y = ypos;
}

void YinYen::setXY(unsigned int x, unsigned int y)
{
    xpos = x;
    ypos = y;
}