#ifndef YINYEN_H
#define YINYEN_H


class YinYen
{
public:
    YinYen();
    YinYen(int x, int y, int status);
    ~YinYen();
    void setStatus(int status);
    int getStatus();
    void getXY(int &x, int &y);

private:
    int xpos;
    int ypos;
    unsigned int stat;
};

#endif // YINYEN_H
