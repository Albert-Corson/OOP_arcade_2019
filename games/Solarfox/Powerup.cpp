/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Powerup
*/

#include "GameAsset.hpp"

using namespace arcade;

Game::Powerup::Powerup(Game &owner, ent_type::_t type, double x, double y, int orient)
    : Asset(owner, type, x, y, orient)
{
}

Game::Powerup::~Powerup()
{
    _owner.getCore().playAudio(audio::POWERUP);
}
