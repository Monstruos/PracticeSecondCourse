#include "menu.h"

Menu::Menu():game(NULL),
             xsize(10),
             ysize(11),
             chFlag(true)
{
    winMenu = new RenderWindow(VideoMode(400, 200), "Menu", sf::Style::Close);

    font.loadFromFile("sup/arial.ttf");
    xText.setFont(font);
    yText.setFont(font);
    head.setFont(font);

    head.setCharacterSize(23);
    head.setString("Parameters(Up, Down,\nLeft, Right - change,\n Enter - openGameWindow):");
    head.setPosition(50, 10);
    head.setColor(Color::White);

    ch.setSize(Vector2f(35, 35));
    ch.setFillColor(Color::Red);
}

Menu::~Menu() {
    if(winMenu != NULL)
        delete winMenu;

    if(game != NULL)
        delete game;
}

void Menu::execute() {
    while (winMenu->isOpen())
    {
        sf::Event event;
        EvHandle(event);
        winMenu->clear();
        DrawParams();
        winMenu->display();
    }
}

void Menu::openGameWindow() {
    game = new GameField(xsize, ysize);
    game->show();
}

void Menu::EvHandle(Event event) {
    while(winMenu->pollEvent(event))
    {
        switch(event.type)
        {
            case Event::Closed:
                winMenu->close();
                break;
            case Event::KeyPressed:
                switch(event.key.code)
                {
                    case Keyboard::Up:
                        if(chFlag) {
                            if(xsize < 50)
                                xsize++;
                        } else {
                            if(ysize < 35)
                                ysize++;
                        }
                        break;
                    case Keyboard::Down:
                        if(chFlag) {
                            if(xsize > 5)
                                xsize--;
                        } else {
                            if(ysize > 5)
                                ysize--;
                        }
                        break;
                    case Keyboard::Left:
                    case Keyboard::Right:
                    chFlag ? chFlag = false : chFlag = true;
                        break;
                    case Keyboard::Return:
                        winMenu->close();
                        openGameWindow();
                        break;
                }
                break;
        }
    }
}

void Menu::DrawParams() {
    winMenu->draw(head);
    if(chFlag)
        ch.setPosition(100, 100);
    else
        ch.setPosition(300, 100);
    winMenu->draw(ch);
    String size;
    std::stringstream istr;
    istr << xsize;
    size = istr.str();
    xText.setString(size);
    xText.setColor(Color::White);
    xText.setPosition(100, 100);
    winMenu->draw(xText);

    istr.str("");
    istr.clear();
    istr << ysize;
    size = istr.str();
    yText.setString(size);
    yText.setColor(Color::White);
    yText.setPosition(300, 100);
    winMenu->draw(yText);
}