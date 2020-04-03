/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Enemy
*/

#include "GameAsset.hpp"

#define MOVE_TIMER 250.0
#define SHOOT_TIMER MOVE_TIMER * 5.0
#define DISABLED_TIMER 2000.0

using namespace arcade;

Game::Enemy::Enemy(Game &owner, ent_type::_t type, double x, double y, int orient)
    : Asset(owner, type, x, y, orient)
    , _speed(1.0)
    , _active(true)
    , _shootClock { _owner.createClock(), 0 }
{
}

void Game::Enemy::process()
{
    static const std::unordered_map<int, void (Enemy::*)()> subProcess = {
        { UP, &Enemy::_processUp },
        { DOWN, &Enemy::_processDown },
        { LEFT, &Enemy::_processLeft },
        { RIGHT, &Enemy::_processRight },
    };
    long elapsed = _mainClock.first->getElapsedTime();

    if (_paused)
        return;
    if (!_active) {
        if (elapsed >= DISABLED_TIMER) {
            _mainClock.second += elapsed - DISABLED_TIMER;
            _shootClock.second = 0;
            _mainClock.first->reset();
            _shootClock.first->reset();
            _active = true;
        }
        return;
    }
    (this->*subProcess.at(orientation))();
}

void Game::Enemy::pause()
{
    if (!_paused)
        _shootClock.second += _shootClock.first->getElapsedTime();
    else
        _shootClock.first->reset();
    Asset::pause();
}

void Game::Enemy::_processUp()
{
    _moveHor();
}

void Game::Enemy::_processDown()
{
    _moveHor();
}

void Game::Enemy::_processLeft()
{
    _moveVert();
}

void Game::Enemy::_processRight()
{
    _moveVert();
}

double Game::Enemy::_move()
{
    long elapsed = _mainClock.first->getElapsedTime();
    double ret = 0;

    if (_mainClock.second + elapsed >= 10) {
        ret = (double)(_mainClock.second + elapsed) / MOVE_TIMER * _speed;
        _mainClock.second = 0;
        _mainClock.first->reset();
    }
    return (ret);
}

void Game::Enemy::_moveHor()
{
    double step = _move();

    posX += step;
    if (posX < 1.0) {
        posX = 1.0 + (1.0 - posX);
        _speed *= -1;
    } else if (posX > (double)Game::boardSizeX - 1.0) {
        posX = (double)Game::boardSizeX - 1.0 - ((double)Game::boardSizeX - 1.0 - posX);
        _speed *= -1;
    }
}

void Game::Enemy::_moveVert()
{
    double step = _move();

    posY += step;
    if (posY < 1.0) {
        posY = 1.0 + (1.0 - posY);
        _speed *= -1;
    } else if (posY > (double)Game::boardSizeY - 1.0) {
        posY = (double)Game::boardSizeY - 1.0 - ((double)Game::boardSizeY - 1.0 - posY);
        _speed *= -1;
    }
}
