/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Enemy
*/

#include "GameAsset.hpp"

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
        if (elapsed >= E_DISABLED_TIMER) {
            _mainClock.second += elapsed - E_DISABLED_TIMER;
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

void Game::Enemy::disable()
{
    _active = false;
}

void Game::Enemy::_processUp()
{
    _moveHor();
    if (_canShoot())
        _shoot(posX, posY - 1, UP);
}

void Game::Enemy::_processDown()
{
    _moveHor();
    if (_canShoot())
        _shoot(posX, posY + 1, DOWN);
}

void Game::Enemy::_processLeft()
{
    _moveVert();
    if (_canShoot())
        _shoot(posX - 1, posY, LEFT);
}

void Game::Enemy::_processRight()
{
    _moveVert();
    if (_canShoot())
        _shoot(posX + 1, posY, RIGHT);
}

double Game::Enemy::_move()
{
    long elapsed = _mainClock.first->getElapsedTime();
    double ret = 0;

    if (_mainClock.second + elapsed >= 10) {
        ret = (double)(_mainClock.second + elapsed) / E_MOVE_TIMER * _speed;
        _mainClock.second += elapsed - 10;
        _mainClock.first->reset();
    }
    return (ret);
}

void Game::Enemy::_moveHor()
{
    const double limX = Game::boardSizeX;
    double step = _move();

    posX += step;
    if (posX < 1.0) {
        posX = 1.0 + (1.0 - posX);
        _speed = 1;
    } else if (posX >= limX) {
        posX = limX - (limX - posX);
        _speed = -1;
    }
}

void Game::Enemy::_moveVert()
{
    const double limY = Game::boardSizeY;
    double step = _move();

    posY += step;
    if (posY < 1.0) {
        posY = 1.0 + (1.0 - posY);
        _speed = 1;
    } else if (posY >= limY) {
        posY = limY - (limY - posY);
        _speed = -1;
    }
}

bool Game::Enemy::_canShoot()
{
    if (!_laser.expired())
        return (false);

    long elapsed = _shootClock.first->getElapsedTime();

    if (_shootClock.second + elapsed > E_SHOOT_TIMER) {
        _shootClock.second += elapsed - E_SHOOT_TIMER;
        _shootClock.first->reset();
        return (true);
    }
    return (false);
}

void Game::Enemy::_shoot(double x, double y, orientation_t dir)
{
    _laser = _owner.addEnemyLaser(x, y, dir);
}
