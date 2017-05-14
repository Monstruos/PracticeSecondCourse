#include "button.h"

Button::Button(): xsize(22),
                  ysize(22),
                  xpos(0),
                  ypos(0)
{
    bColor.r = 128;
    bColor.g = 128;
    bColor.b = 128;
    tColor = Color::White;
    button.setSize(Vector2f(xsize, ysize));
    button.setFillColor(bColor);
    button.setPosition(Vector2f(xpos, ypos));
    font.loadFromFile("sup/arial.ttf");
    input.setFont(font);
    input.setCharacterSize(ysize - 6);
    input.setPosition(xpos + 3, ypos + 3);

}

Button::Button(unsigned int _xpos, unsigned int _ypos, unsigned int _xsize, unsigned int _ysize, Color _bColor, Color _tColor):
        xsize(_xsize),
        ysize(_ysize),
        xpos(_xpos),
        ypos(_ypos)
{
    bColor = _bColor;
    tColor = _tColor;
    button.setSize(Vector2f(xsize, ysize));
    button.setFillColor(bColor);
    button.setPosition(Vector2f(xpos, ypos));
    font.loadFromFile("sup/arial.ttf");
    input.setFont(font);
    input.setString(" ");
    input.setColor(tColor);
    input.setCharacterSize(ysize - 6);
    input.setPosition(xpos + 3, ypos + 3);

}

Button::~Button() {

}

void Button::setPos(float x, float y) {
    xpos = x;
    ypos = y;
    button.setPosition(x, y);
    input.setPosition(x+3, y+3);
}

void Button::setSize(float a, float b) {
    xsize = a;
    ysize = b;
    button.setSize(Vector2f(xsize, ysize));
    input.setCharacterSize(ysize - 6);
}

void Button::setText(const String &filename) {
    input.setString(filename);
}

void Button::setColorText(Color &color) {
    tColor = color;
    input.setColor(tColor);
}

void Button::setColor(Color &color) {
    bColor = color;
    button.setFillColor(bColor);
}

void Button::Draw(RenderWindow *window) {
    if(window != NULL)
    {
        window->draw(button);
        window->draw(input);
    }
}