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
{
    _keyActions = {
        {Key::DOWN, &Game::moveDown},
        {Key::UP, &Game::moveUp},
        {Key::RIGHT, &Game::moveRight},
        {Key::LEFT, &Game::moveLeft},
        {Key::SPACE, &Game::pause},
    };
    for (const auto &it : _keyActions)
        _actionKeys.push_back(KeyState(it.first));
    initMap();
    initSnake();
    initAssets();
}

void Game::initAssets()
{
    _core.loadResourceImage(1, "games/Snake/assets/limit.png", "games/Snake/assets/limit");
    _core.loadResourceImage(3, "games/Snake/assets/head.png", "games/Snake/assets/head");
    _core.loadResourceImage(4, "games/Snake/assets/body.png", "games/Snake/assets/body");
    _core.loadResourceImage(5, "games/Snake/assets/tail.png", "games/Snake/assets/tail");
    _core.loadResourceImage(6, "games/Snake/assets/fruit.png", "games/Snake/assets/fruit");
    _core.loadResourceFont(0, "games/Snake/assets/font.ttf");
}

void Game::initMap()
{
    for (int y = 0; y < 40; y += 1) {
        for (int x = 0; x < 60; x += 1) {
            if (y == 0 || x == 0 || y == 39 || x == 59)
                _map.push_back({x, y, '1'});
            else
                _map.push_back({x, y, '0'});
        }
    }
}

void Game::initSnake()
{
    _snake.push_back({21, 21, '3'});
    _snake.push_back({22, 21, '4'});
    _snake.push_back({23, 21, '4'});
    _snake.push_back({24, 21, '5'});
    newFruit();
}

void Game::launch()
{
    std::unique_ptr<IClock> cl = _core.createClock();
    double idx = 0.00;

    srand(time(NULL));
    _running = true;
    _gameState = -1;
    while (_running)
        sceneGame(cl, idx);
    this->stop();
}

void Game::sceneGame(std::unique_ptr<IClock> &cl, double &idx)
{
    int x = _map.back().x + 2;
    std::vector<std::string> state = {"PAUSE", "YOU LOSE", "RUN"};

    if (_gameState == 1)
        idx = cl->getElapsedTime() / 100.00 * 2;
    if (cl->getElapsedTime() > 50) {
        _core.getKeyboardEvents(_actionKeys);
        processKeys(idx);
        if (_gameState == 1)
            idx = 0.00;
        if (!_actionKeys[0].is_pressed)
            cl->reset();
    }
    _core.clear();
    displayAssets(idx);
    displayKeys(x);
    _core.displayText(0, x, 1, state[_gameState + 1] + "\tSCORE :  " + std::to_string(getScore()));
    _core.render();
}

void Game::processKeys(double &idx)
{
    if (_actionKeys[0].is_pressed)
        pause();
    else if (_gameState == 1)
        gameMotor();
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
}

Key Game::onlyOneKey()
{
    int count = 0;
    Key keyPress;

    for (size_t i = 1; i < _actionKeys.size(); i++) {
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

    if (_lastKey != UNKNOWN && key != _lastKey && inTail)
        return (this->*_keyActions[_lastKey])(_lastKey);
    _lastKey = key;
    moveTail();
    _snake[0].x += x;
    _snake[0].y += y;
    if (m == '6')
        eatFruit();
    if (m == '1' || m == '4' || m == '5')
        _gameState = 0;
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
    addScore(1);
    newFruit();
}

void Game::newFruit(void)
{
    size_t i = 0;

    while (getMap()[i].val != '0')
        i = rand() % _map.size();
    _map[i].val = '6';
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

void Game::displayKeys(const int x)
{
    _core.displayText(0, x, 3, "ACTIONS");
    _core.displayText(0, x + 6, 3, "| RUN");
    _core.displayText(0, x, 4, "-------------------------------");
    _core.displayText(0, x, 5, "'space'");
    _core.displayText(0, x + 6, 5, "| pause");
    _core.displayText(0, x, 6, "'arrows'");
    _core.displayText(0, x + 6, 6, "| change direction");
    _core.displayText(0, x, 7, "-------------------------------");
    _core.displayText(0, x, 8, "'F1'");
    _core.displayText(0, x + 6, 8, "| Previous library");
    _core.displayText(0, x, 9, "'F2'");
    _core.displayText(0, x + 6, 9, "| Next library");
    _core.displayText(0, x, 10, "'F3'");
    _core.displayText(0, x + 6, 10, "| Previous game");
    _core.displayText(0, x, 11, "'F4'");
    _core.displayText(0, x + 6, 11, "| Next game");
    _core.displayText(0, x, 12, "'F5'");
    _core.displayText(0, x + 6, 12, "| Restart game");
    _core.displayText(0, x, 13, "'F6'");
    _core.displayText(0, x + 6, 13, "| Back to menu");
    _core.displayText(0, x, 14, "'F7'");
    _core.displayText(0, x + 6, 14, "| Exit");
}
