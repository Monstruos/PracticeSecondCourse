#include "field.h"

GameField::GameField() : xsize(10),
                         ysize(10),
                         map(NULL),
                         window(NULL),
                         cl(NULL),
                         nextmap(NULL),
                         isPlaying(0)
{
    mapInit();
    screen.x = xsize*20 + 252;
    screen.y = ysize*20 + 2;
    window = new RenderWindow;
    window->create(VideoMode(screen.x, screen.y), "Yin-Yen", Style::Close);
    backTxt.loadFromFile("sup/back.jpeg");
    backTxt.setSmooth(true);
    back = new RectangleShape(Vector2f(screen.x, screen.y));
    back->setTexture(&backTxt, true);

    font.loadFromFile("sup/arial.ttf");
    text.setFont(font);
    text.setString("LMB - set/remove Yin\nRMB - set/remove Yen\nSpace - start/stop game");
    text.setCharacterSize(20);
    text.setColor(Color::Green);
    text.setPosition(Vector2f(xsize*20 + 10, 2));
    cl = new Clock;
}

GameField::GameField(unsigned int x, unsigned int y) : xsize(x),
                                                       ysize(y),
                                                       map(NULL),
                                                       window(NULL),
                                                       cl(NULL),
                                                       nextmap(NULL),
                                                       isPlaying(false)
{
    mapInit();
    screen.x = xsize*20 + 252;
    screen.y = ysize*20 + 2;
    window = new RenderWindow;
    window->create(VideoMode(screen.x, screen.y), "Yin-Yen", Style::Close);
    backTxt.loadFromFile("sup/back.jpeg");
    backTxt.setSmooth(true);
    back = new RectangleShape(Vector2f(screen.x, screen.y));
    back->setTexture(&backTxt, true);

    font.loadFromFile("sup/arial.ttf");
    text.setFont(font);
    text.setString("LMB - set/remove Yin\nRMB - set/remove Yen\nSpace - start/stop game");
    text.setCharacterSize(20);
    text.setColor(Color::Green);
    text.setPosition(Vector2f(xsize*20 + 10, 2));
    cl = new Clock;
}

GameField::~GameField() {
    mapClear();
    delete cl;
}

void GameField::next()
{
    unsigned int i, j;
    int curStat;
    int New;
    bool stopGen = true;
    nextmap = new YinYen** [xsize];
    for(i = 0; i < xsize; ++i)
    {
        nextmap[i] = new YinYen *[ysize];
        for(j = 0; j < ysize; ++j)
        {
            curStat = map[i][j]->getStatus();
            nextmap[i][j] = new YinYen(i, j, curStat);
            if(isDead(i, j))
                nextmap[i][j]->setStatus(EMPTY);
            New = isNew(i, j);
            if(New != 0)
                nextmap[i][j]->setStatus(New);
            if(nextmap[i][j]->getStatus() != curStat)
                stopGen = false;
        }
    }
    if(stopGen)
        isPlaying = false;
    mapClear();
    map = nextmap;
    nextmap = NULL;
}

void GameField::show() {
    while (window->isOpen())
    {
        sf::Event event;
        eventHandler(event);
        if(isPlaying && cl != NULL) {
            elapse = cl->getElapsedTime();
            if(elapse.asSeconds() >= 0.5f){
                cl->restart();
                next();
            }
        }
        window->draw(*back);
        window->draw(text);
        drawMap();
        drawInterface();
        window->display();
    }
}

bool GameField::isDead(int x, int y) {
    if(map[x][y]->getStatus() == EMPTY)
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

int GameField::isNew(int x, int y) {
    if(map[x][y]->getStatus() != EMPTY)
        return EMPTY;
    int res, count;
    checkAdjacent(x, y, &res, &count);

    if(count == 3)
    {
        if(res == 1)
            return YIN;
        if(res == -1)
            return YEN;
    }
    return EMPTY;
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

void GameField::mapInit() {
    map = new YinYen** [xsize];
    for(unsigned int i = 0; i < xsize; ++i) {
        map[i] = new YinYen *[ysize];
        for(unsigned int j = 0; j < ysize; ++j)
            map[i][j] = new YinYen(i, j);
    }
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
    RectangleShape linesx(Vector2f(2, ysize*20 + 2));
    RectangleShape linesy(Vector2f(xsize*20 + 2, 2));
    for(i = 0; i <= xsize; ++i) {
        linesx.setPosition(Vector2f(i*20, 0));
        window->draw(linesx);
    }
    for(i = 0; i <= ysize; ++i) {
        linesy.setPosition(Vector2f(0, i*20));
        window->draw(linesy);
    }

}

void GameField::drawMap() {
    CircleShape *dr;
    if(window != NULL)
        for(int i = 0; i < xsize; ++i)
            for(int j = 0; j < ysize; ++j) {
                dr = map[i][j]->getCell();
                if(dr != NULL)
                    window->draw(*dr);
            }
}

void GameField::eventHandler(Event event) {
    int x, y;
    if(window->pollEvent(event));
    {
        switch(event.type) {
            case Event::Closed:
                window->close();
                break;

            case Event::LostFocus:
                if (isPlaying)
                    isPlaying = 0;
                break;

            case Event::MouseButtonPressed:
                x = (event.mouseButton.x - 1) / 20;
                y = (event.mouseButton.y - 1) / 20;
                if (x >= 0 && x < xsize && y >= 0 && y < ysize && !isPlaying) {
                    if (event.mouseButton.button == Mouse::Left) {

                        if (map[x][y]->getStatus() >= 0)
                            map[x][y]->setStatus(YIN);
                        else
                            map[x][y]->setStatus(EMPTY);
                    }
                    if (event.mouseButton.button == Mouse::Right) {
                        if (map[x][y]->getStatus() <= 0)
                            map[x][y]->setStatus(YEN);
                        else
                            map[x][y]->setStatus(EMPTY);

                    }
                }
                break;

            case Event::KeyPressed:
                if(event.key.code == Keyboard::Space)
                    if(isPlaying)
                        isPlaying = false;
                    else
                        isPlaying = true;

                if(event.key.code == Keyboard::Escape)
                    window->close();
                break;

            default:
                break;
        }
    }
}