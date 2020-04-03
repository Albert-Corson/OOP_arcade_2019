/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Player
*/

#include "GameAsset.hpp"

using namespace arcade;

Game::Player::Player(Game &owner, ent_type::_t type, double x, double y, int orient)
    : Asset(owner, type, x, y, orient)
{
}

void Game::Player::process()
{
}

void Game::Player::pause()
{
    Asset::pause();
}
