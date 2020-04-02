/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Game
*/

#include "Game.hpp"
#include "assets.hpp"

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
        { Key::UP, &Game::_setPlayerDir },
        { Key::DOWN, &Game::_setPlayerDir },
        { Key::LEFT, &Game::_setPlayerDir },
        { Key::RIGHT, &Game::_setPlayerDir },
        { Key::SPACE, &Game::_playerShoot },
        { Key::P, &Game::_pause }
    };

    for (const auto &it : _keyActions)
        _actionKeys.push_back(KeyState(it.first));
    _loadAssets();
}

void Game::launch()
{
    _running = true;

    while (_running) {
        _core.clear();
        _core.render();
        _core.getKeyboardEvents(_actionKeys);
        _processKeys();
    }
}

void Game::_loadAssets() 
{
    for (const auto &it : IMAGES_TO_LOAD)
        _core.loadResourceImage(it.first, PATH_TO_ASSETS + it.second.first, PATH_TO_ASSETS + it.second.second);
    for (const auto &it : FONTS_TO_LOAD)
        _core.loadResourceFont(it.first, PATH_TO_ASSETS + it.second);
    for (const auto &it : AUDIOS_TO_LOAD)
        _core.loadResourceAudio(it.first, PATH_TO_ASSETS + it.second);
}

void Game::_processKeys()
{
    for (const auto &it : _actionKeys) {
        if (it.is_pressed)
            (this->*_keyActions[it.key])(it.key);
    }
}

void Game::_setPlayerDir(Key key)
{
    throw "TO DO";
}

void Game::_playerShoot(Key key)
{
    throw "TO DO";
}

void Game::_pause(Key key)
{
    _paused = !_paused;
}
