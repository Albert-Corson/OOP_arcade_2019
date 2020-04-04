/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** EnemyLaser
*/

#include "GameAsset.hpp"

using namespace arcade;

Game::EnemyLaser::EnemyLaser(Game &owner, ent_type::_t type, double x, double y, int orient)
    : Asset(owner, type, x, y, orient)
{
    _owner.getCore().playAudio(audio::ENEMY_LASER);
}

void Game::EnemyLaser::process()
{
    _move();
}

bool Game::EnemyLaser::isDead()
{
    if (posX < 1.0 || posX >= Game::boardSizeX)
        return (true);
    else if (posY < 1.0 || posY >= Game::boardSizeY)
        return (true);
    if (_mainClock.first->getElapsedTime() + _mainClock.second >= E_SHOOT_TIMER * 2)
        return (true);
    return (false);
}

void Game::EnemyLaser::_move()
{
    static const std::unordered_map<int, void (EnemyLaser::*)(double)> moves {
        { UP, &EnemyLaser::_moveUp },
        { DOWN, &EnemyLaser::_moveDown },
        { LEFT, &EnemyLaser::_moveLeft },
        { RIGHT, &EnemyLaser::_moveRight }
    };
    long elapsed = _mainClock.first->getElapsedTime();
    double step = 0;

    if (_mainClock.second + elapsed >= 10) {
        step = (double)(_mainClock.second + elapsed) / EL_MOVE_TIMER;
        _mainClock.second += elapsed - 10;
        _mainClock.first->reset();
    }
    (this->*moves.at(orientation))(step);
}

void Game::EnemyLaser::_moveUp(double step)
{
    posY -= step;
}

void Game::EnemyLaser::_moveDown(double step)
{
    posY += step;
}

void Game::EnemyLaser::_moveLeft(double step)
{
    posX -= step;
}

void Game::EnemyLaser::_moveRight(double step)
{
    posX += step;
}
