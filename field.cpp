#include "field.h"

GameField::GameField(unsigned int x, unsigned int y) : xsize(x),
                                                       ysize(y),
                                                       map(NULL),
                                                       window(NULL),
                                                       cl(NULL),
                                                       nextmap(NULL),
                                                       isPlaying(0)
{
    mapInit();
    xscreen = xsize*30 + 2;
    yscreen = ysize*30 + 2;
    window = new RenderWindow;
    window->create(VideoMode(xscreen, yscreen), "Yin-Yen", Style::Default);
    backTxt.loadFromFile("texture/back.jpeg", IntRect(0, 0, xscreen, yscreen));
    backTxt.setSmooth(true);
    back = new RectangleShape(Vector2f(xscreen, yscreen));
    back->setTexture(&backTxt, true);
    Yin = new CircleShape(6.f);
    Yin->setFillColor(Color::White);
    Yin->setOutlineThickness(7);
    Yin->setOutlineColor(Color::Black);

    Yen = new CircleShape(6.f);
    Yen->setFillColor(Color::Black);
    Yen->setOutlineThickness(7);
    Yen->setOutlineColor(Color::White);
    cl = new Clock;
}

GameField::~GameField() {
    mapClear();
    delete Yin;
    delete Yen;
    delete cl;
}

void GameField::mapInit() {
    map = new YinYen** [xsize];
    for(unsigned int i = 0; i < xsize; ++i) {
        map[i] = new YinYen *[ysize];
        for(unsigned int j = 0; j < ysize; ++j)
            map[i][j] = new YinYen(i, j);
    }

}

void GameField::show() {
    while (window->isOpen())
    {
        sf::Event event;
        eventHandler(event);
        if(isPlaying && cl != NULL) {
            elapse = cl->getElapsedTime();
            if(elapse.asSeconds() >= 1.f){
                cl->restart();
                next();
            }
        }
        window->draw(*back);
        drawMap();
        drawInterface();
        window->display();
    }
    return;
}

void GameField::checkAdjacent(int x, int y, int *res, int *number) {
    int bufStat;
    *res = 0;
    *number = 0;
    int K[8][2] = {
            {-1, -1},
            {-1,  0},
            {-1,  1},
            { 0, -1},
            { 0,  1},
            { 1, -1},
            { 1,  0},
            { 1,  1}
    };
    int kx, ky;
    int i;
    for(i = 0; i < 8; ++i)
    {
        kx = x+K[i][0];
        ky = y+K[i][1];
        if(kx >= 0 && ky >= 0 &&
           kx < xsize && ky < ysize)
        {
            bufStat = map[kx][ky]->getStatus();
            if(bufStat != 0)
            {
                *res += bufStat;
                (*number)++;
            }
        }
    }
}

int GameField::isNew(int x, int y) {
    if(map[x][y]->getStatus() != 0)
        return 0;
    int res, count;
    checkAdjacent(x, y, &res, &count);

    if(count == 3)
    {
        if(res == 1)
            return -1;
        if(res == -1)
            return 1;
    }
    return 0;
}

bool GameField::isDead(int x, int y) {
    if(map[x][y]->getStatus() == 0)
        return true;

    int res, count;
    checkAdjacent(x, y, &res, &count);

    if(count < 2 || count > 4)
        return true;

    if(count == 4)
        if((map[x][y]->getStatus() * res) < 0)
            return true;

    return false;
}

void GameField::next()
{
    unsigned int i, j;
    bool stopGen = true;
    nextmap = new YinYen** [xsize];
    for(i = 0; i < xsize; ++i)
    {
        nextmap[i] = new YinYen *[ysize];
        for(j = 0; j < ysize; ++j)
        {
            nextmap[i][j] = new YinYen(i, j, map[i][j]->getStatus());
            if(isDead(i, j))
                nextmap[i][j]->setStatus(0);
            int New = isNew(i, j);
            if(New != 0)
                nextmap[i][j]->setStatus(New);
            if(nextmap[i][j]->getStatus() != map[i][j]->getStatus())
                stopGen = false;
        }
    }
    if(stopGen)
        isPlaying = false;
    mapClear();
    map = nextmap;
    nextmap = NULL;
}

void GameField::mapClear() {
    if(map != NULL) {
        for (int i = 0; i < xsize; ++i) {
            for(int j = 0; j < ysize; ++j)
                delete map[i][j];
            delete[] map[i];
        }
        delete[] map;
        map = NULL;
    }
}
void GameField::drawInterface() {
    int i;
    RectangleShape linesx(Vector2f(2, ysize*30 + 2));
    RectangleShape linesy(Vector2f(xsize*30 + 2, 2));
    for(i = 0; i <= xsize; ++i) {
        linesx.setPosition(Vector2f(i*30, 0));
        window->draw(linesx);
    }
    for(i = 0; i <= ysize; ++i) {
        linesy.setPosition(Vector2f(0, i*30));
        window->draw(linesy);
    }

}

void GameField::drawMap() {
    if(window != NULL)
        for(int i = 0; i < xsize; ++i)
            for(int j = 0; j < ysize; ++j)
                switch(map[i][j]->getStatus())
                {
                    case 1:
                        Yen->setPosition(Vector2f(10+i*30, 10+j*30));
                        window->draw(*Yen);
                        break;
                    case 0:
                        break;
                    case -1:
                        Yin->setPosition(Vector2f(10+i*30, 10+j*30));
                        window->draw(*Yin);
                        break;
                    default:
                        break;
                }
}

void GameField::eventHandler(Event event) {
    if(window->pollEvent(event));
    {
        switch(event.type)
        {
            case Event::Closed:
                window->close();
                break;
            case Event::MouseButtonPressed:
                if(event.mouseButton.button == Mouse::Left && !isPlaying) {
                    int x = (event.mouseButton.x - 1) / 30;
                    int y = (event.mouseButton.y - 1) / 30;
                    if (x >= 0 && x < xsize && y >= 0 && y < ysize) {
                        if (map[x][y]->getStatus() >= 0)
                            map[x][y]->setStatus(-1);
                        else
                            map[x][y]->setStatus(0);
                    }
                }
                if(event.mouseButton.button == Mouse::Right && !isPlaying) {
                    int x = (event.mouseButton.x - 1) / 30;
                    int y = (event.mouseButton.y - 1) / 30;
                    if (x >= 0 && x < xsize && y >= 0 && y < ysize) {
                        if (map[x][y]->getStatus() <= 0) {
                            map[x][y]->setStatus(1);
                        } else {
                            map[x][y]->setStatus(0);
                        }
                    }
                }
                break;
            case Event::KeyPressed:
                if(event.key.code == Keyboard::Space)
                    if(isPlaying){
                        isPlaying = false;
                    } else {
                        isPlaying = true;
                    }
                if(event.key.code == Keyboard::Escape)
                    window->close();
                break;
            default:
                break;
        }
    }
}