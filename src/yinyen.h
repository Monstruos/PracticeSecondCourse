#define YIN -1
#define EMPTY 0
#define YEN 1

#include <SFML/Graphics.hpp>

using namespace sf;

class YinYen
{
public:
    YinYen();
    YinYen(unsigned int x, unsigned int y, int status = EMPTY);
    ~YinYen();
    void setStatus(int status);
    int getStatus();
    CircleShape *getCell();

private:
    unsigned int xpos;
    unsigned int ypos;
    int stat;
    CircleShape *cell;
};