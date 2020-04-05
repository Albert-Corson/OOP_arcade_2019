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
            _map.push_back({x, y, a, UNKNOWN, 0.00});
            x += 1;
        }
    }
}

void Game::initPacman()
{
    for (auto &it : _map) {
        if (it.val == '3') {
            _players.push_back(it);
            it.val = '0';
        }
    }
    for (auto &it : _map) {
        if (it.val == '1') {
            _players.push_back(it);
            it.val = '0';
        }
    }
}

void Game::resetGame()
{
    _map.clear();
    _players.clear();
    setScore(0);
    initMap();
    initPacman();
    _gameState = -1;
}

void Game::launch()
{
    std::unique_ptr<IClock> cl = _core.createClock();
    int map = _currentMap;
    unsigned long bestScore = 0;

    srand(time(NULL));
    _running = true;
    _gameState = -1;
    bestScore = 0;
    while (_running) {
        sceneGame(cl, map);
        if (_gameState == 0 && bestScore < getScore())
            bestScore = getScore();
    }
    setScore(bestScore);
    this->stop();
}

void Game::sceneGame(std::unique_ptr<IClock> &cl, int &map)
{
    int x = _map.back().x + 2;
    std::vector<std::string> state = {"PAUSE", "YOU WIN", "RUN", "YOU LOSE"};

    if (_gameState == 1) {
        for (auto &it : _players)
            it.gap = cl->getElapsedTime() / 100.00;
    } if (cl->getElapsedTime() > 100) {
        _core.getKeyboardEvents(_actionKeys);
        processKeys(map);
        if (_gameState == 1) {
            for (auto &it : _players)
                it.gap = 0.00;
        } if (!_actionKeys[1].is_pressed)
            cl->reset();
    }
    _core.clear();
    displayAssets();
    displayKeys(x, map);
    _core.displayText(0, x, 1, state[_gameState + 1] + "\tSCORE :  " + std::to_string(getScore()));
    _core.render();
}

void Game::changeMap(int &map)
{
    if (_actionKeys[0].is_pressed && map != _currentMap) {
        _currentMap = map;
        resetGame();
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

void Game::processKeys(int &map)
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
        changeMap(map);
}

void Game::pause(Key key, int i)
{
    if (_gameState == 1 || _gameState == -1)
        _gameState = -_gameState;
}

void Game::gameMotor()
{
    Key move = UNKNOWN;

    for (size_t i = 0; i < _players.size(); i += 1) {
        if (i == 0)
            move = onlyOneKey();
        else
            move = dirEnemies(possibleDir(i), i);
        if (move != UNKNOWN) {
            (this->*_keyActions[move])(move, i);
        }
    }
    checkFruit();
}

std::vector<Key> Game::possibleDir(int i)
{
    std::vector<Key> dirs;

    if (canMove(i, RIGHT) && originMove(i) != RIGHT)
        dirs.push_back(RIGHT);
    if (canMove(i, LEFT) && originMove(i) != LEFT)
        dirs.push_back(LEFT);
    if (canMove(i, UP) && originMove(i) != UP)
        dirs.push_back(UP);
    if (canMove(i, DOWN) && originMove(i) != DOWN)
        dirs.push_back(DOWN);
    if (dirs.size() == 0)
        dirs.push_back(UNKNOWN);
    return dirs;
}

Key Game::originMove(int id)
{
    switch (_players[id].lastMove)
    {
    case RIGHT: return LEFT;
    case LEFT: return RIGHT;
    case UP: return DOWN;
    case DOWN: return UP;
    default: return UNKNOWN;
    }
}

Key Game::dirEnemies(const std::vector<Key> &dirs, int id)
{
    int i;

    if (dirs.size() == 1 && dirs[0] == UNKNOWN)
        return originMove(id);
    else if (dirs.size() == 1)
        return dirs[0];
    i = rand() % dirs.size();
    return dirs[i];
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
    return _players[0].lastMove;
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

    for (size_t i = 0; i < _players.size(); i++) {
        tmp[getPos(_players[i].x, _players[i].y)].val = _players[i].val;
    }
    return tmp;
}

void Game::moveDown(Key key, int i)
{
    movePlayers(0, 1, key, i);
}

void Game::moveUp(Key key, int i)
{
    movePlayers(0, -1, key, i);
}

void Game::moveRight(Key key, int i)
{
    movePlayers(1, 0, key, i);
}

void Game::moveLeft(Key key, int i)
{
    movePlayers(-1, 0, key, i);
}

void Game::movePlayers(const int x, const int y, const Key key, int i)
{
    char m = getMap()[getPos(_players[0].x + x, _players[0].y + y)].val;

    if (i != 0)
        return (moveEnemies(x, y, key, i));
    if (_players[0].lastMove != UNKNOWN && key != _players[0].lastMove && m == '2')
        return (this->*_keyActions[_players[0].lastMove])(_players[0].lastMove, 0);
    if (m != '2') {
        _players[0].lastMove = key;
        _players[0].x += x;
        _players[0].y += y;
        teleportation(0);
        if (m == '6')
            eatFruit();
    }
    else
        _players[0].lastMove = UNKNOWN;
    if (m == '1') {
        _gameState = 2;
        setScore(0);
    }
}

void Game::moveEnemies(const int x, const int y, const Key key, int i)
{
    char m = getMap()[getPos(_players[i].x + x, _players[i].y + y)].val;
    Key move;

    if (m != '2' && m != '1') {
        _players[i].lastMove = key;
        _players[i].x += x;
        _players[i].y += y;
        if (_players[i].x == 0)
            _players[i].x = _map.back().x - 1;
        if (_players[i].x == _map.back().x)
            _players[i].x = 1;
        teleportation(i);
    }
    else {
        move = dirEnemies(possibleDir(i), i);
        (this->*_keyActions[move])(move, i);
    }
    if (m == '3') {
        _gameState = 2;
        setScore(0);
    }
}

void Game::teleportation(int i)
{
    if (_players[i].x == 0)
        _players[i].x = _map.back().x - 1;
    if (_players[i].x == _map.back().x)
        _players[i].x = 1;
    if (_players[i].y == 0)
        _players[i].y = _map.back().y - 1;
    if (_players[i].y == _map.back().y)
        _players[i].y = 1;
}

void Game::eatFruit(void)
{
    _map[getPos(_players[0].x, _players[0].y)].val = '0';
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

bool Game::canMove(const size_t i, const Key dir)
{
    std::vector<pos_t> map = getMap();
    char r = map[getPos(_players[i].x + 1, _players[i].y)].val;
    char l = map[getPos(_players[i].x - 1, _players[i].y)].val;
    char u = map[getPos(_players[i].x, _players[i].y - 1)].val;
    char d = map[getPos(_players[i].x, _players[i].y + 1)].val;

    if (dir == UNKNOWN)
        return true;
    else if ((dir == Key::RIGHT && r != '0' && r != '6' && r != '3') ||
        (dir == Key::LEFT && l != '0' && l != '6' && l != '3') ||
        (dir == Key::UP && u != '0' && u != '6' && u != '3') ||
        (dir == Key::DOWN && d != '0' && d != '6' && d != '3'))
        return false;
    return true;
}

void Game::displayAssets()
{
    double idx;

    for (auto &it : _map) {
        if (it.val != '0')
            _core.displayImage(atoi(&it.val), it.x, it.y);
    }
    for (int i = _players.size() - 1; i >= 0; i -= 1) {
        idx = _players[i].gap;
        if (_players[i].lastMove == UNKNOWN || !canMove(i, _players[i].lastMove))
            idx = 0;
        switch (_players[i].lastMove)
        {
        case Key::LEFT:
            _core.displayImage(atoi(&_players[i].val), _players[i].x - idx, (double)_players[i].y);
            break;
        case Key::RIGHT:
            _core.displayImage(atoi(&_players[i].val), _players[i].x + idx, (double)_players[i].y);
            break;
        case Key::UP:
            _core.displayImage(atoi(&_players[i].val), (double)_players[i].x, _players[i].y - idx);
            break;
        case Key::DOWN:
            _core.displayImage(atoi(&_players[i].val), (double)_players[i].x, _players[i].y + idx);
            break;
        default:
            _core.displayImage(atoi(&_players[i].val), _players[i].x, _players[i].y);
            break;
        }
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
