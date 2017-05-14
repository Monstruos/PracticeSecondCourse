#ifndef BUTTON_H_
#define BUTTON_H_

#include <SFML/Graphics.hpp>

using namespace sf;

class Button
{
private:
    unsigned int xsize;
    unsigned int ysize;
    float xpos;
    float ypos;
    Font font;
    Text input;
    RectangleShape button;
    Color bColor;
    Color tColor;
public:
    Button();
    Button(unsigned int _xpos = 0, unsigned int _ypos = 0, unsigned int _xsize = 22, unsigned int _ysize = 22,
           Color _bColor = Color(128, 128, 128), Color _tColor = Color::White);
    ~Button();
    void setPos(float x, float y);
    void setColor(Color &color);
    void setText(const String &filename);
    void setColorText(Color &color);
    void setSize(float a, float b);
    void Draw(RenderWindow *window);
};

#endif // BUTTON_H_