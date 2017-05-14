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
    (status < 2 && status > -2) ? stat = status : stat = EMPTY;
}

YinYen::~YinYen()
{

}

void YinYen::setStatus(int status)
{
    (status < 2 && status > -2) ? stat = status : stat = EMPTY;
}

int YinYen::getStatus()
{
    return stat;
}