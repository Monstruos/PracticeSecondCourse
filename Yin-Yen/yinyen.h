#ifndef YINYEN_H
#define YINYEN_H


class YinYen
{
public:
    YinYen();
    YinYen(int x, int y, unsigned int status);
    ~YinYen();
    void setStatus(unsigned int status);
    int getStatus(unsigned int status);
    void getXY(int &x, int &y);
private:
    int xpos;
    int ypos;
    unsigned int stat;
};

#endif // YINYEN_H
