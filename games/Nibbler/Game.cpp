/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Game
*/

#include "Game.hpp"
#include <iostream>

using namespace arcade;

Game::Game(ICore &core)
    : AGame(core)
    , _gameState(1)
    , _lastKey(LEFT)
    , _currentMap(1)
{
    _keyActions = {
        {Key::DOWN, &Game::moveDown},
        {Key::UP, &Game::moveUp},
        {Key::RIGHT, &Game::moveRight},
        {Key::LEFT, &Game::moveLeft},
        {Key::SPACE, &Game::pause},
    };
    _actionKeys.push_back(KeyState(Key::ENTER));
    for (const auto &it : _keyActions)
        _actionKeys.push_back(KeyState(it.first));
    initMap();
    initSnake('3');
    initAssets();
}

void Game::initAssets()
{
    _core.loadResourceImage(1, "games/Nibbler/assets/limit.png", "games/Nibbler/assets/limit");
    _core.loadResourceImage(2, "games/Nibbler/assets/wall.png", "games/Nibbler/assets/wall");
    _core.loadResourceImage(3, "games/Nibbler/assets/head.png", "games/Nibbler/assets/head");
    _core.loadResourceImage(4, "games/Nibbler/assets/body.png", "games/Nibbler/assets/body");
    _core.loadResourceImage(5, "games/Nibbler/assets/tail.png", "games/Nibbler/assets/tail");
    _core.loadResourceImage(6, "games/Nibbler/assets/fruit.png", "games/Nibbler/assets/fruit");
    _core.loadResourceFont(0, "games/Nibbler/assets/font.ttf");
}

void Game::initMap(void)
{
    int x = 0;
    int y = 0;
    std::ifstream file("games/Nibbler/assets/map" + std::to_string(_currentMap));
    char a;

    while (file.get(a)) {
        if (a == '\n') {
            x = 0;
            y += 1;
        }
        else {
            _map.push_back({x, y, a});
            x += 1;
        }
    }
}

void Game::initSnake(const char id)
{
    for (auto &it : _map) {
        if (it.val == id) {
            _snake.push_back(it);
            it.val = '0';
        }
    }
    if (id < '5')
        initSnake(id + 1);
}

void Game::resetGame()
{
    _map.clear();
    _snake.clear();
    setScore(0);
    initMap();
    initSnake('3');
    _lastKey = LEFT;
    _gameState = -1;
}

void Game::launch()
{
    std::unique_ptr<IClock> cl = _core.createClock();
    double idx = 0.00;
    int map = _currentMap;
    unsigned long bestScore = 0;

    _running = true;
    _gameState = -1;
    bestScore = 0;
    while (_running) {
        sceneGame(cl, idx, map);
        if (_gameState == 0 && bestScore < getScore())
            bestScore = getScore();
    }
    setScore(bestScore);
    this->stop();
}

void Game::sceneGame(std::unique_ptr<IClock> &cl, double &idx, int &map)
{
    int x = _map.back().x + 2;
    std::vector<std::string> state = {"PAUSE", "YOU WIN", "RUN", "YOU LOSE"};

    if (_gameState == 1)
        idx = cl->getElapsedTime() / 100.00;
    if (cl->getElapsedTime() > 100) {
        _core.getKeyboardEvents(_actionKeys);
        processKeys(map, idx);
        if (_gameState == 1) {
            addScore(1);
            idx = 0.00;
        }
        if (!_actionKeys[1].is_pressed)
            cl->reset();
    }
    _core.clear();
    displayAssets(idx);
    displayKeys(x, map);
    _core.displayText(0, x, 1, state[_gameState + 1] + "\tSCORE :  " + std::to_string(getScore()));
    _core.render();
}

void Game::changeMap(int &map, double &idx)
{
    if (_actionKeys[0].is_pressed && map != _currentMap) {
        _currentMap = map;
        resetGame();
        idx = 0;
        return;
    }
    if (_actionKeys[2].is_pressed && !_actionKeys[3].is_pressed) {
        map -= 1;
        if (map < 1)
            map = 3;
    }
    else if (_actionKeys[3].is_pressed && !_actionKeys[2].is_pressed) {
        map += 1;
        if (map > 3)
            map = 1;
    }
}

void Game::processKeys(int &map, double &idx)
{
    if (_actionKeys[1].is_pressed) {
        pause();
        return;
    }
    if (_gameState == 1) {
        gameMotor();
        map = _currentMap;
    }
    else
        changeMap(map, idx);
}

void Game::pause(Key key)
{
    if (_gameState == 1 || _gameState == -1)
    _gameState = -_gameState;
}

void Game::gameMotor()
{
    Key move = onlyOneKey();

    if (move != UNKNOWN) {
        (this->*_keyActions[move])(move);
    }
    checkFruit();
}

Key Game::onlyOneKey()
{
    int count = 0;
    Key keyPress;

    for (size_t i = 2; i < _actionKeys.size(); i++) {
        if (_actionKeys[i].is_pressed) {
            keyPress = _actionKeys[i].key;
            count++;
        }
    }
    if (count == 1)
        return keyPress;
    return _lastKey;
}

int Game::getPos(int x, int y)
{
    for (size_t i = 0; i < _map.size(); i++) {
        if (_map[i].x == x && _map[i].y == y)
            return i;
    }
    return 0;
}

std::vector<pos_t> Game::getMap()
{
    std::vector<pos_t> tmp = _map;

    for (size_t i = 0; i < _snake.size(); i++) {
        tmp[getPos(_snake[i].x, _snake[i].y)].val = _snake[i].val;
    }
    return tmp;
}

void Game::moveDown(Key key)
{
    moveSnake(0, 1, key);
}

void Game::moveUp(Key key)
{
    moveSnake(0, -1, key);
}

void Game::moveRight(Key key)
{
    moveSnake(1, 0, key);
}

void Game::moveLeft(Key key)
{
    moveSnake(-1, 0, key);
}

void Game::moveSnake(const int x, const int y, const Key key)
{
    int i = getPos(_snake[0].x + x, _snake[0].y + y);
    char m = getMap()[i].val;
    bool inTail = (_map[i].x == _snake[1].x && _map[i].y == _snake[1].y);

    if (_lastKey != UNKNOWN && key != _lastKey && (m == '2' || inTail))
        return (this->*_keyActions[_lastKey])(_lastKey);
    if (m != '2') {
        _lastKey = key;
        moveTail();
        _snake[0].x += x;
        _snake[0].y += y;
        if (m == '6')
            eatFruit();
    }
    else
        _lastKey = UNKNOWN;
    if (m == '1' || m == '4' || m == '5') {
        _gameState = 2;
        setScore(0);
    }
}

void Game::moveTail(void)
{
    for (size_t i = _snake.size() - 1; i > 0; i--) {
        _snake[i].x = _snake[i - 1].x;
        _snake[i].y = _snake[i - 1].y;
    }
}

void Game::eatFruit(void)
{
    size_t i = _snake.size() - 1;

    _map[getPos(_snake[0].x, _snake[0].y)].val = '0';
    _snake.push_back(_snake[i]);
    _snake[i].val = '4';
}

void Game::checkFruit(void)
{
    for (size_t i = 0; i < _map.size(); i++) {
        if (_map[i].val == '6')
            return;
    }
    _gameState = 0;
}

bool Game::canMove()
{
    char r = _map[getPos(_snake[0].x + 1, _snake[0].y)].val;
    char l = _map[getPos(_snake[0].x - 1, _snake[0].y)].val;
    char u = _map[getPos(_snake[0].x, _snake[0].y - 1)].val;
    char d = _map[getPos(_snake[0].x, _snake[0].y + 1)].val;

    if (_lastKey == UNKNOWN)
        return true;
    else if ((_lastKey == Key::RIGHT && r != '0' && r != '6') ||
        (_lastKey == Key::LEFT && l != '0' && l != '6') ||
        (_lastKey == Key::UP && u != '0' && u != '6') ||
        (_lastKey == Key::DOWN && d != '0' && d != '6'))
        return false;
    return true;
}

void Game::displayAssets(double idx)
{
    for (auto &it : _map) {
        if (it.val != '0')
            _core.displayImage(atoi(&it.val), it.x, it.y);
    }
    for (size_t i = 0; i < _snake.size(); i += 1) {
        if (_lastKey == UNKNOWN || !canMove())
            idx = 0;
        switch (snakeDirection(i))
        {
        case Key::LEFT:
           _core.displayImage(atoi(&_snake[i].val), _snake[i].x - idx, (double)_snake[i].y);
            break;
        case Key::RIGHT:
           _core.displayImage(atoi(&_snake[i].val), _snake[i].x + idx, (double)_snake[i].y);
            break;
        case Key::UP:
           _core.displayImage(atoi(&_snake[i].val), (double)_snake[i].x, _snake[i].y - idx);
            break;
        case Key::DOWN:
           _core.displayImage(atoi(&_snake[i].val), (double)_snake[i].x, _snake[i].y + idx);
            break;
        default:
           _core.displayImage(atoi(&_snake[i].val), _snake[i].x, _snake[i].y);
            break;
        }
    }
}

Key Game::snakeDirection(size_t i)
{
    if (i == 0)
        return _lastKey;
    if (_snake[i].x > _snake[i-1].x)
        return Key::LEFT;
    if (_snake[i].x < _snake[i-1].x)
        return Key::RIGHT;
    if (_snake[i].y > _snake[i-1].y)
        return Key::UP;
    if (_snake[i].y < _snake[i-1].y)
        return Key::DOWN;
    return Key::UNKNOWN;
}

void Game::displayKeys(const int x, const int map)
{
    _core.displayText(0, x, 3, "ACTIONS");
    _core.displayText(0, x + 6, 3, "|\tRUN");
    _core.displayText(0, x + 20, 3, "|\tPAUSE");
    _core.displayText(0, x, 4, "-----------------------------------------");
    _core.displayText(0, x, 5, "'space'");
    _core.displayText(0, x + 6, 5, "|\tpause");
    _core.displayText(0, x + 20, 5, "|\trun");
    _core.displayText(0, x, 6, "'arrows'");
    _core.displayText(0, x + 6, 6, "|\tchange direction");
    _core.displayText(0, x + 20, 6, "|\tchange map");
    _core.displayText(0, x, 7, "'enter'");
    _core.displayText(0, x + 6, 7, "|\tnothing");
    _core.displayText(0, x + 20, 7, "|\tvalid new map");
    _core.displayText(0, x, 8, "-----------------------------------------");
    _core.displayText(0, x, 9, "'F1'");
    _core.displayText(0, x + 6, 9, "|\tPrevious library");
    _core.displayText(0, x, 10, "'F2'");
    _core.displayText(0, x + 6, 10, "|\tNext library");
    _core.displayText(0, x, 11, "'F3'");
    _core.displayText(0, x + 6, 11, "|\tPrevious game");
    _core.displayText(0, x, 12, "'F4'");
    _core.displayText(0, x + 6, 12, "|\tNext game");
    _core.displayText(0, x, 13, "'F5'");
    _core.displayText(0, x + 6, 13, "|\tRestart game");
    _core.displayText(0, x, 14, "'F6'");
    _core.displayText(0, x + 6, 14, "|\tBack to menu");
    _core.displayText(0, x, 15, "'F7'");
    _core.displayText(0, x + 6, 15, "|\tExit");
    _core.displayText(0, x, 17, "<   map" + std::to_string(map) + "  >");
}
