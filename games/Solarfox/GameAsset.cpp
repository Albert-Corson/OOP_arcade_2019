/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** GameAsset
*/

#include "Game.hpp"

using namespace arcade;

Game::Asset::Asset(Game::entity_type_t type, double x, double y, Game::orientation_t orient)
    : etype(type)
    , posX(x)
    , posY(y)
    , orientation(orient)
{
}

Game::image_t Game::Asset::getImage() const noexcept
{
    return static_cast<Game::image_t>((int)etype | orientation);
}

void Game::Asset::setPosition(double x, double y) noexcept
{
    posX = x;
    posY = y;
}

void Game::Asset::setPosition(double x, double y, Game::orientation_t orient) noexcept
{
    setPosition(x, y);
    setOrientation(orient);
}

void Game::Asset::setOrientation(Game::orientation_t orient) noexcept
{
    orientation = orient;
}
