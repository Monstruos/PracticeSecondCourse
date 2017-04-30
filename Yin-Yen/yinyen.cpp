#include "yinyen.h"

YinYen::YinYen() :
    xpos(0),
    ypos(0),
    stat(0)
{

}

YinYen::YinYen(int x, int y, unsigned int status = 0) :
    xpos(x),
    ypos(y)
{
    status < 3 ? stat = status : stat = 0;
}

YinYen::~YinYen()
{

}

void YinYen::setStatus(unsigned int status)
{
    stat = status;
}

int YinYen::getStatus(unsigned int status)
{
    return status;
}

void YinYen::getXY(int &x, int &y)
{
    x = xpos;
    y = ypos;
}
