#define YIN -1
#define EMPTY 0
#define YEN 1

class YinYen
{
public:
    YinYen();
    YinYen(unsigned int x, unsigned int y, int status = EMPTY);
    ~YinYen();
    void setStatus(int status);
    int getStatus();

private:
    unsigned int xpos;
    unsigned int ypos;
    int stat;
};