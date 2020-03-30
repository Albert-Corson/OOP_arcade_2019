/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** GameMenu
*/

#include <string>
#include <vector>
#include <unordered_map>
#include "deps/keys.hpp"
#include "core/ICore.hpp"
#include "GameMenu.hpp"

using namespace arcade;

GameMenu::GameMenu(ICore &core)
    : AGame(core)
{
    _core.loadResourceFont(F_MENUS, "menu/assets/digitalt-regular.ttf");
    _core.loadResourceImage(I_ARROW, "menu/assets/arrow.png", "menu/assets/arrow.ascii");
}

GameMenu::~GameMenu()
{
}

void GameMenu::_drawMenu()
{
    _core.displayText(F_MENUS, 2, 0, "Pacman");
    _core.displayText(F_MENUS, 2, 1, "Nibbler");
    _core.displayText(F_MENUS, 2, 2, "SolarFox");
    _core.displayImage(I_ARROW, (double)0, (double)_currItem);
}

void GameMenu::_keyNextItem()
{
    ++_currItem;
}

void GameMenu::_keyPrevItem()
{
    --_currItem;
}

void GameMenu::_keyNextTab()
{
    ++_currTab;
}

void GameMenu::_keyPrevTab()
{
    --_currTab;
}

void GameMenu::_keySelect()
{
    
}

void GameMenu::_handleEvents()
{
    static std::unordered_map<Key, keyAction> actions = {
        { Key::ENTER, &arcade::GameMenu::_keySelect },
        { Key::LEFT, &arcade::GameMenu::_keyPrevTab },
        { Key::RIGHT, &arcade::GameMenu::_keyNextTab },
        { Key::DOWN, &arcade::GameMenu::_keyNextItem },
        { Key::UP, &arcade::GameMenu::_keyPrevItem }
    };
    static std::vector<arcade::KeyState> keys = {
        arcade::KeyState(arcade::Key::ENTER),
        arcade::KeyState(arcade::Key::LEFT),
        arcade::KeyState(arcade::Key::RIGHT),
        arcade::KeyState(arcade::Key::DOWN),
        arcade::KeyState(arcade::Key::UP)
    };

    _core.getKeyboardEvents(keys);
    for (const auto &it: keys) {
        if (it.is_pressed)
            (this->*actions[it.key])();
    }
}

void GameMenu::launch()
{
    _running = true;

    while (_running) {
        _core.clear();
        _drawMenu();
        _core.render();
        _handleEvents();
    }
}

void GameMenu::stop()
{
    _running = false;
}