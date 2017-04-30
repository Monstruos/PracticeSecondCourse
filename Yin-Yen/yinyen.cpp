#include "yinyen.h"

YinYen::YinYen() :
    xpos(0),
    ypos(0),
    stat(0)
{

}

YinYen::YinYen(int x, int y, int status = 0) :
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
    stat = status;
}

int YinYen::getStatus()
{
    return stat;
}

void YinYen::getXY(int &x, int &y)
{
    x = xpos;
    y = ypos;
}
