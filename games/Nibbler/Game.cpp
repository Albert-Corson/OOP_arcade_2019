/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Game
*/

#include "Game.hpp"
#include <iostream>

using namespace arcade;

std::string get_lib_name()
{
    return ("Nibbler");
}

std::unique_ptr<arcade::IGame> init_game_lib(arcade::ICore& core)
{
    return (std::make_unique<Game>(core));
}

Game::Game(ICore &core)
    : AGame(core)
    , _gameState(1)
    , _lastKey(UNKNOWN)
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
    initSnake('3');
    initAssets();
}

void Game::launch()
{
    std::unique_ptr<IClock> cl = _core.createClock();
    double idx = 0.00;

    _running = true;
    while (_running) {
        idx = cl->getElapsedTime() / 100.00;
        if (cl->getElapsedTime() > 100) {
            _core.getKeyboardEvents(_actionKeys);
            processKeys();
            cl->reset();
            idx = 0.00;
        }
        _core.clear();
        displayAssets(idx);
        _core.render();
    }
    this->stop();
}

void Game::initAssets()
{
    _core.loadResourceImage(1, "games/Nibbler/assets/limit.png", "games/Nibbler/assets/limit");
    _core.loadResourceImage(2, "games/Nibbler/assets/wall.png", "games/Nibbler/assets/wall");
    _core.loadResourceImage(3, "games/Nibbler/assets/head.png", "games/Nibbler/assets/head");
    _core.loadResourceImage(4, "games/Nibbler/assets/body.png", "games/Nibbler/assets/body");
    _core.loadResourceImage(5, "games/Nibbler/assets/tail.png", "games/Nibbler/assets/tail");
    _core.loadResourceImage(6, "games/Nibbler/assets/fruit.png", "games/Nibbler/assets/fruit");
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

void Game::initMap(void)
{
    int x = 0;
    int y = 0;
    std::ifstream file("games/Nibbler/assets/map1");
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

void Game::processKeys()
{
    int i = 0;

    if (_actionKeys[i].is_pressed)
        pause();
    else
        gameMotor();
}

void Game::pause(Key key)
{
    _gameState = -_gameState;
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

void Game::gameMotor()
{
    Key move = onlyOneKey();

    if (move != UNKNOWN) {
        (this->*_keyActions[move])(move);
    }
    checkFruit();
}

int Game::getPos(int x, int y)
{
    for (size_t i = 0; i < _map.size(); i++) {
        if (_map[i].x == x && _map[i].y == y)
            return i;
    }
    return -1;
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

std::vector<pos_t> Game::getMap()
{
    std::vector<pos_t> tmp = _map;

    for (size_t i = 0; i < _snake.size(); i++) {
        tmp[getPos(_snake[i].x, _snake[i].y)].val = _snake[i].val;
    }
    return tmp;
}

void Game::moveSnake(const int x, const int y, const Key key)
{
    int i = getPos(_snake[0].x + x, _snake[0].y + y);
    char m = getMap()[i].val;
    bool inTail = (_map[i].x == _snake[1].x && _map[i].y == _snake[1].y);

    if (_lastKey != UNKNOWN && key != _lastKey && (m == '2' || inTail))
        return (this->*_keyActions[_lastKey])(_lastKey);
    if (m == '0' || m == '6') {
        _lastKey = key;
        moveTail();
        _snake[0].x += x;
        _snake[0].y += y;
        if (m == '6')
            eatFruit();
    }
    else
        _lastKey = UNKNOWN;
    if (m == '1' || m == '4' || m == '5')
        _gameState = 2;
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
