/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** GameAsset
*/

#include "GameAsset.hpp"

using namespace arcade;

Game::Asset::Asset(Game &owner, Game::ent_type::_t type, double x, double y, int orient)
    : etype(type)
    , posX(x)
    , posY(y)
    , orientation(orient)
    , _paused(true)
    , _owner(owner)
    , _mainClock { owner.createClock(), 0 }
{
}

Game::Asset::operator int() const noexcept
{
    return (getImage());
}

Game::image::_t Game::Asset::getImage() const noexcept
{
    return static_cast<Game::image::_t>(etype | orientation);
}

void Game::Asset::setPosition(double x, double y) noexcept
{
    posX = x;
    posY = y;
}

void Game::Asset::setPosition(double x, double y, int orient) noexcept
{
    setPosition(x, y);
    setOrientation(orient);
}

void Game::Asset::setOrientation(int orient) noexcept
{
    orientation = orient;
}

void Game::Asset::display(ICore &core) const
{
    core.displayImage(getImage(), posX, posY);
}

void Game::Asset::process()
{
}

void Game::Asset::pause()
{
    if (!_paused)
        _mainClock.second += _mainClock.first->getElapsedTime();
    else
        _mainClock.first->reset();
    _paused = !_paused;
}
