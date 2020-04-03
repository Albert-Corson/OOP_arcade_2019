/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** GameAsset
*/

#include "Game.hpp"

using namespace arcade;

Game::Asset::Asset(Game::ent_type::_t type, double x, double y, int orient)
    : etype(type)
    , posX(x)
    , posY(y)
    , orientation(orient)
    , clock(nullptr)
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

void Game::Asset::resetClock(ICore &core)
{
    if (clock == nullptr)
        clock = core.createClock();
    else
        clock->reset();
}

long Game::Asset::getElapsedTime(bool reset)
{
    long elapsed = clock->getElapsedTime();

    if (reset)
        clock->reset();
    return (elapsed);
}
