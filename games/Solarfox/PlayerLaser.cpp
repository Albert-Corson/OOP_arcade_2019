/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** PlayerLaser
*/

#include "GameAsset.hpp"

using namespace arcade;

Game::PlayerLaser::PlayerLaser(Game &owner, ent_type::_t type, double x, double y, int orient)
    : Asset(owner, type, x, y, orient)
{
    _owner.getCore().playAudio(audio::PLAYER_LASER);
}

void Game::PlayerLaser::process()
{
    _move();
}

bool Game::PlayerLaser::isDead()
{
    if (posX < 1.0 || posX >= Game::boardSizeX)
        return (true);
    else if (posY < 1.0 || posY >= Game::boardSizeY)
        return (true);
    if (_mainClock.first->getElapsedTime() + _mainClock.second >= P_SHOOT_TIMER)
        return (true);
    return (false);
}

void Game::PlayerLaser::_move()
{
    static const std::unordered_map<int, void (PlayerLaser::*)(double)> moves {
        { UP, &PlayerLaser::_moveUp },
        { DOWN, &PlayerLaser::_moveDown },
        { LEFT, &PlayerLaser::_moveLeft },
        { RIGHT, &PlayerLaser::_moveRight }
    };
    long elapsed = _mainClock.first->getElapsedTime();
    double step = 0;

    if (_mainClock.second + elapsed >= 10) {
        step = (double)(_mainClock.second + elapsed) / PL_MOVE_TIMER;
        _mainClock.second += elapsed - 10;
        _mainClock.first->reset();
    }
    (this->*moves.at(orientation))(step);
}

void Game::PlayerLaser::_moveUp(double step)
{
    posY -= step;
}

void Game::PlayerLaser::_moveDown(double step)
{
    posY += step;
}

void Game::PlayerLaser::_moveLeft(double step)
{
    posX -= step;
}

void Game::PlayerLaser::_moveRight(double step)
{
    posX += step;
}
