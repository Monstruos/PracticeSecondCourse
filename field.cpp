#include "field.h"

GameField::GameField(unsigned int x, unsigned int y) : xsize(x), ysize(y), map(NULL), window(NULL), isPlaying(0){
    mapInit();
    xscreen = xsize*30 + 2;
    yscreen = ysize*30 + 2;

    window = new RenderWindow;
    window->create(sf::VideoMode(xscreen, yscreen), "Yin-Yen", sf::Style::Default);
    drawInterface();
}

GameField::~GameField() {
    mapClear();
}

void GameField::mapInit() {
    map = new YinYen** [xsize];
    for(int i = 0; i < xsize; ++i) {
        map[i] = new YinYen *[ysize];
        for(int j = 0; j < ysize; ++j)
            map[i][j] = new YinYen(i, j);
    }
}

void GameField::show() {
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear(Color(0, 100, 0));
        drawInterface();
        window->display();
    }
    return;
}

void GameField::checkAdjacent(int x, int y, int &res, int &number) {
    int bufStat;
    res = 0;
    number = 0;
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
                res += bufStat;
                number++;
            }
        }
    }
}

int GameField::isNew(int x, int y) {
    if(map[x][y]->getStatus() != 0)
        return 0;
    int res, count;
    checkAdjacent(x, y, res, count);

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
    checkAdjacent(x, y, res, count);

    if(count < 2 || count > 4)
        return true;

    if(count == 4)
        if((map[x][y]->getStatus() * res) < 0)
            return true;

    return false;
}

void GameField::next()
{
    YinYen ***nextmap;
    nextmap = new YinYen** [xsize];
    for(int i = 0; i < xsize; ++i)
    {
        nextmap[i] = new YinYen *[ysize];
        for(int j = 0; j < ysize; ++j)
        {
            nextmap[i][j] = new YinYen(i, j);
            int notEmpty = map[i][j]->getStatus();
            int New = isNew(i, j);
            if(notEmpty == 0 && New != 0)
                nextmap[i][j]->setStatus(New);

            if(isDead(i, j))
                nextmap[i][j]->setStatus(0);
        }
    }
    mapClear();
    map = nextmap;
}

void GameField::mapClear() {
    if(map != NULL) {
        for (int i = 0; i < xsize; ++i) {
            for(int j = 0; j < ysize; ++j)
                delete map[i][j];
            delete[] map[i];
        }
        delete[] map;
    }
}
void GameField::drawInterface() {
    int i;
    RectangleShape *linesx = new RectangleShape [xsize + 1];
    RectangleShape *linesy = new RectangleShape [ysize + 1];
    for(i = 0; i <= xsize; ++i) {
        linesx[i].setSize(Vector2f(2, ysize*30 + 2));
        linesx[i].setPosition(Vector2f(i*30, 0));
        window->draw(linesx[i]);
    }
    for(i = 0; i <= ysize; ++i) {
        linesy[i].setSize(Vector2f(xsize*30 + 2, 2));
        linesy[i].setPosition(Vector2f(0, i*30));
        window->draw(linesy[i]);
    }
}