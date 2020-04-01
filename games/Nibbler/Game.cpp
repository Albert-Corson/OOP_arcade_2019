/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Game
*/

#include "Game.hpp"

using namespace arcade;

std::string get_lib_name()
{
    return ("Nibbler");
}

std::unique_ptr<arcade::IGame> init_game_lib(arcade::ICore& core)
{
    return (std::make_unique<Game>(core));
}

Game::Game(ICore &core)
    : AGame(core)
{
}

void Game::launch()
{
    _running = true;

    this->stop();
}
