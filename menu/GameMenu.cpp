/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** GameMenu
*/

#include <string>
#include "core/ICore.hpp"
#include "GameMenu.hpp"

using namespace arcade;

GameMenu::GameMenu(ICore &core)
    : AGame(core)
    , _running(false)
{
}

GameMenu::~GameMenu()
{
}

void GameMenu::launch()
{
    _running = true;
    int count = 0;

    while (_running) {
        _core.clear();
        _core.displayText(0, 0, 0, "Hello world");
        _core.render();
        this->stop();
    }
}

void GameMenu::stop()
{
    _running = false;
}