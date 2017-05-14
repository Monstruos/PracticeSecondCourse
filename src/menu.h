#include "field.h"
#include <sstream>

class Menu
{
public:
    Menu();
    ~Menu();
    void execute();
    void openGameWindow();

protected:
    void EvHandle(Event event);
    void DrawParams();

private:
    unsigned int xsize;
    unsigned int ysize;
    bool chFlag;
    Font font;
    Text xText;
    Text yText;
    Text head;
    RenderWindow *winMenu;
    RectangleShape ch;
    GameField *game;
};