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
    return ("Solar Fox");
}

std::unique_ptr<arcade::IGame> init_game_lib(arcade::ICore &core)
{
    return (std::make_unique<Game>(core));
}

Game::Game(ICore &core)
    : AGame(core)
    , _paused(false)
{
    _keyActions = {
        { Key::UP, &Game::setPlayerDir },
        { Key::DOWN, &Game::setPlayerDir },
        { Key::LEFT, &Game::setPlayerDir },
        { Key::RIGHT, &Game::setPlayerDir },
        { Key::SPACE, &Game::playerShoot },
        { Key::P, &Game::pause }
    };

    for (const auto &it : _keyActions)
        _actionKeys.push_back(KeyState(it.first));
}

void Game::launch()
{
    _running = true;

    while (_running) {
        _core.clear();
        _core.render();
        _core.getKeyboardEvents(_actionKeys);
        processKeys();
    }
}

void Game::processKeys()
{
    for (const auto &it : _actionKeys) {
        if (it.is_pressed)
            (this->*_keyActions[it.key])(it.key);
    }
}

void Game::setPlayerDir(Key key)
{
    throw "TO DO";
}

void Game::playerShoot(Key key)
{
    throw "TO DO";
}

void Game::pause(Key key)
{
    _paused = !_paused;
}
