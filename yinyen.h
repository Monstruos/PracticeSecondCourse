#define YIN -1
#define EMPTY 0
#define YEN 1

class YinYen
{
public:
    YinYen();
    YinYen(unsigned int x, unsigned int y, int status = 0);
    ~YinYen();
    void setStatus(int status);
    int getStatus();
    void getXY(unsigned int &x, unsigned int &y);
    void setXY(unsigned int x, unsigned int y);

private:
    unsigned int xpos;
    unsigned int ypos;
    int stat;
};