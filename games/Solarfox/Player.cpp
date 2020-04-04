/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Player
*/

#include "GameAsset.hpp"
#include <cmath>

using namespace arcade;

Game::Player::Player(Game &owner, ent_type::_t type, double x, double y, int orient)
    : Asset(owner, type, x, y, orient)
{
}

void Game::Player::process()
{
    _move();
    if (_isDead())
        _owner.stop();
}

void Game::Player::shoot()
{
    if (_laser.expired())
        _laser = _owner.addPlayerLaser(posX, posY, (orientation_t)orientation);
}

bool Game::Player::_isDead()
{
    if (posX < 1.0 || posX >= Game::boardSizeX)
        return (true);
    else if (posY < 1.0 || posY >= Game::boardSizeY)
        return (true);
    return (false);
}

void Game::Player::_move()
{
    static int lastDir = orientation;
    static const std::unordered_map<int, void (Player::*)(double, int)> moves {
        { UP, &Player::_moveUp },
        { DOWN, &Player::_moveDown },
        { LEFT, &Player::_moveLeft },
        { RIGHT, &Player::_moveRight }
    };
    long elapsed = _mainClock.first->getElapsedTime();
    double step = 0;

    if (_mainClock.second + elapsed >= 10) {
        step = (double)(_mainClock.second + elapsed) / P_MOVE_TIMER;
        _mainClock.second = 0;
        _mainClock.first->reset();
    }
    (this->*moves.at(orientation))(step, lastDir);
    if (lastDir != orientation)
        lastDir = orientation;
}

void Game::Player::_moveUp(double step, int lastDir)
{
    posY -= step;
}

void Game::Player::_moveDown(double step, int lastDir)
{
    posY += step;
}

void Game::Player::_moveLeft(double step, int lastDir)
{
    posX -= step;
}

void Game::Player::_moveRight(double step, int lastDir)
{
    posX += step;
}
