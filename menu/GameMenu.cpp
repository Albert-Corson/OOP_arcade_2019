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

extern "C" std::unique_ptr<IGame> init_menu_lib(ICore &core)
{
    return (std::make_unique<GameMenu>(core));
}

GameMenu::GameMenu(ICore &core)
    : AGame(core)
    , _currTab(1)
    , _currItem(0)
    , _tabs({ "Graphics", "Games" })
    , _items({
        _core.getLibGraphsList(),
        _core.getGamesList()
    })
{
    _keyActions = {
        { Key::ENTER, &arcade::GameMenu::_keySelect },
        { Key::LEFT, &arcade::GameMenu::_keyPrevTab },
        { Key::RIGHT, &arcade::GameMenu::_keyNextTab },
        { Key::DOWN, &arcade::GameMenu::_keyNextItem },
        { Key::UP, &arcade::GameMenu::_keyPrevItem }
    };
    for (const auto &it : _keyActions)
        _actionKeys.push_back(KeyState(it.first));

    _core.loadResourceFont(F_MENUS, "menu/assets/digitalt-regular.ttf");
    _core.loadResourceImage(I_ARROW, "menu/assets/arrow.png", "menu/assets/arrow.ascii");
}

GameMenu::~GameMenu()
{
}

void GameMenu::_drawMenu()
{
    size_t posx = 0;
    size_t posy = 0;
    size_t index = 0;

    // Display tabs (beginning with the current tab)
    auto currTabIt = _tabs.begin() + _currTab;
    auto tabIt = currTabIt;
    while (tabIt != _tabs.end()) {
        _core.displayText(F_MENUS, posx, posy, *tabIt);
        posx += tabIt->length() + 1;
        ++tabIt;
    }
    tabIt = _tabs.begin();
    while (tabIt != currTabIt) {
        _core.displayText(F_MENUS, posx, posy, *tabIt);
        posx += tabIt->length() + 1;
        ++tabIt;
    }

    // Display items
    posx = 2;
    posy = 2;
    _core.displayImage(I_ARROW, 0.0f, (double)(posy + _currItem));
    for (const auto &itemIt: _items[_currTab]) {
        _core.displayText(F_MENUS, posx, posy, itemIt.name);
        ++posy;
    }
}

void GameMenu::_keyNextItem()
{
    if (_currItem < _items[_currTab].size() - 1)
        ++_currItem;
    else
        _currItem = 0;
}

void GameMenu::_keyPrevItem()
{
    if (_currItem > 0)
        --_currItem;
    else
        _currItem = _items[_currTab].size() - 1;
}

void GameMenu::_keyNextTab()
{
    if (_currTab < _tabs.size() - 1)
        ++_currTab;
    else
        _currTab = 0;
    _currItem = 0;
}

void GameMenu::_keyPrevTab()
{
    if (_currTab > 0)
        --_currTab;
    else
        _currTab = _tabs.size() - 1;
    _currItem = 0;
}

void GameMenu::_keySelect()
{
    static std::vector<void (ICore::*)(const std::string)> actions = {
        &ICore::setLibGraph,  // "Graphics" tab
        &ICore::setGame       // "Games" tab
    };

    if (_currTab <= actions.size() - 1) {
        (_core.*actions[_currTab])(_items[_currTab][_currItem].path);
    }
}

void GameMenu::_handleEvents()
{
    _core.getKeyboardEvents(_actionKeys);
    for (const auto &it: _actionKeys) {
        if (it.is_pressed)
            (this->*_keyActions[it.key])();
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