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
    initPacman();
    initAssets();
}

void Game::initAssets()
{
    _core.loadResourceImage(1, "games/Pacman/assets/limit.png", "games/Pacman/assets/limit");
    _core.loadResourceImage(2, "games/Pacman/assets/wall.png", "games/Pacman/assets/wall");
    _core.loadResourceImage(3, "games/Pacman/assets/pacman.png", "games/Pacman/assets/pacman");
    _core.loadResourceImage(6, "games/Pacman/assets/fruit.png", "games/Pacman/assets/fruit");
    _core.loadResourceFont(0, "games/Pacman/assets/font.ttf");
}

void Game::initMap()
{
    int x = 0;
    int y = 0;
    std::ifstream file("games/Pacman/assets/map" + std::to_string(_currentMap));
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

void Game::initPacman()
{
    for (auto &it : _map) {
        if (it.val == '3') {
            _pacman = it;
            it.val = '0';
        }
    }
}

void Game::resetGame()
{
    _map.clear();
    setScore(0);
    initMap();
    initPacman();
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
        if (_gameState == 1)
            idx = 0.00;
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

    tmp[getPos(_pacman.x, _pacman.y)].val = _pacman.val;
    return tmp;
}

void Game::moveDown(Key key)
{
    movePacman(0, 1, key);
}

void Game::moveUp(Key key)
{
    movePacman(0, -1, key);
}

void Game::moveRight(Key key)
{
    movePacman(1, 0, key);
}

void Game::moveLeft(Key key)
{
    movePacman(-1, 0, key);
}

void Game::movePacman(const int x, const int y, const Key key)
{
    int i = getPos(_pacman.x + x, _pacman.y + y);
    char m = getMap()[i].val;

    if (_lastKey != UNKNOWN && key != _lastKey && m == '2')
        return (this->*_keyActions[_lastKey])(_lastKey);
    if (m != '2') {
        _lastKey = key;
        _pacman.x += x;
        _pacman.y += y;
        if (_pacman.x == 0)
            _pacman.x = _map.back().x - 1;
        if (_pacman.x == _map.back().x)
            _pacman.x = 1;
        teleportation();
        if (m == '6')
            eatFruit();
    }
    else
        _lastKey = UNKNOWN;
    if (m == '1') {
        _gameState = 2;
        setScore(0);
    }
}

void Game::teleportation()
{
    if (_pacman.x == 0)
        _pacman.x = _map.back().x - 1;
    if (_pacman.x == _map.back().x)
        _pacman.x = 1;
    if (_pacman.y == 0)
        _pacman.y = _map.back().y - 1;
    if (_pacman.y == _map.back().y)
        _pacman.y = 1;
}

void Game::eatFruit(void)
{
    _map[getPos(_pacman.x, _pacman.y)].val = '0';
    addScore(1);
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
    char r = _map[getPos(_pacman.x + 1, _pacman.y)].val;
    char l = _map[getPos(_pacman.x - 1, _pacman.y)].val;
    char u = _map[getPos(_pacman.x, _pacman.y - 1)].val;
    char d = _map[getPos(_pacman.x, _pacman.y + 1)].val;

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
    if (_lastKey == UNKNOWN || !canMove())
        idx = 0;
    switch (_lastKey)
    {
    case Key::LEFT:
        _core.displayImage(atoi(&_pacman.val), _pacman.x - idx, (double)_pacman.y);
        break;
    case Key::RIGHT:
        _core.displayImage(atoi(&_pacman.val), _pacman.x + idx, (double)_pacman.y);
        break;
    case Key::UP:
        _core.displayImage(atoi(&_pacman.val), (double)_pacman.x, _pacman.y - idx);
        break;
    case Key::DOWN:
        _core.displayImage(atoi(&_pacman.val), (double)_pacman.x, _pacman.y + idx);
        break;
    default:
        _core.displayImage(atoi(&_pacman.val), _pacman.x, _pacman.y);
        break;
    }
}

void Game::displayKeys(const int x, const int map)
{
    _core.displayText(0, x, 3, "ACTIONS");
    _core.displayText(0, x + 6, 3, "| RUN");
    _core.displayText(0, x + 18, 3, "| PAUSE");
    _core.displayText(0, x, 4, "----------------------------------------------");
    _core.displayText(0, x, 5, "'space'");
    _core.displayText(0, x + 6, 5, "| pause");
    _core.displayText(0, x + 18, 5, "| run");
    _core.displayText(0, x, 6, "'arrows'");
    _core.displayText(0, x + 6, 6, "| change direction");
    _core.displayText(0, x + 18, 6, "| change map");
    _core.displayText(0, x, 7, "'enter'");
    _core.displayText(0, x + 6, 7, "| nothing");
    _core.displayText(0, x + 18, 7, "| valid new map");
    _core.displayText(0, x, 8, "----------------------------------------------");
    _core.displayText(0, x, 9, "'F1'");
    _core.displayText(0, x + 6, 9, "| Previous library");
    _core.displayText(0, x, 10, "'F2'");
    _core.displayText(0, x + 6, 10, "| Next library");
    _core.displayText(0, x, 11, "'F3'");
    _core.displayText(0, x + 6, 11, "| Previous game");
    _core.displayText(0, x, 12, "'F4'");
    _core.displayText(0, x + 6, 12, "| Next game");
    _core.displayText(0, x, 13, "'F5'");
    _core.displayText(0, x + 6, 13, "| Restart game");
    _core.displayText(0, x, 14, "'F6'");
    _core.displayText(0, x + 6, 14, "| Back to menu");
    _core.displayText(0, x, 15, "'F7'");
    _core.displayText(0, x + 6, 15, "| Exit");
    _core.displayText(0, x, 17, "<   map" + std::to_string(map) + "  >");
}
