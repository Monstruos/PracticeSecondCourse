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
    cell = new CircleShape(2.f);
    cell->setOutlineThickness(6);
    if(stat == YIN){
        cell->setFillColor(Color::White);
        cell->setOutlineColor(Color::Black);
    }
    if(stat == YEN){
        cell->setFillColor(Color::Black);
        cell->setOutlineColor(Color::White);
    }
    cell->setPosition(Vector2f(9+xpos*20, 9+ypos*20));
}

YinYen::~YinYen()
{

}

void YinYen::setStatus(int status)
{
    (status < 2 && status > -2) ? stat = status : stat = EMPTY;
    if(status == YIN){
        cell->setFillColor(Color::White);
        cell->setOutlineColor(Color::Black);
    }
    if(status == YEN){
        cell->setFillColor(Color::Black);
        cell->setOutlineColor(Color::White);
    }
}

int YinYen::getStatus()
{
    return stat;
}

CircleShape* YinYen::getCell() {
    if(stat == EMPTY)
        return NULL;
    return cell;
}