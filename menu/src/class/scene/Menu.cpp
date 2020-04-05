/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Menu
*/

#include <unordered_map>
#include "class/scene/Menu.hpp"

using namespace arcade;

Menu::Menu(GameMenu &game)
    : AScene(game, {
        Key::ENTER,
        Key::UP,
        Key::DOWN,
        Key::LEFT,
        Key::RIGHT
      })
    , _tabs({
        "Games",
        "Graphics",
        "Scores"
      })
    , _currTab(0)
    , _items({ {}, {}, {} })
    , _currItem(0)
    , _games(_core.getGamesList())
    , _graphics(_core.getLibGraphsList())
    , _scores(_core.getScoreboards())
{
    for (const auto &it: _games)
        _items[0].push_back(it.name);
    for (const auto &it: _graphics)
        _items[1].push_back(it.name);
    for (const auto &it: _scores)
        _items[2].push_back(it.gameName);
}

void Menu::_keyNextItem()
{
    if (_currItem < _items[_currTab].size() - 1)
        ++_currItem;
    else
        _currItem = 0;
}

void Menu::_keyPrevItem()
{
    if (_currItem > 0)
        --_currItem;
    else
        _currItem = _items[_currTab].size() - 1;
}

void Menu::_keyNextTab()
{
    if (_currTab < _tabs.size() - 1)
        ++_currTab;
    else
        _currTab = 0;
    _currItem = 0;
}

void Menu::_keyPrevTab()
{
    if (_currTab > 0)
        --_currTab;
    else
        _currTab = _tabs.size() - 1;
    _currItem = 0;
}

void Menu::_selectGame(std::size_t id, const std::string &item)
{
    _core.setGame(_games[id].path);
}

void Menu::_selectGraphLib(std::size_t id, const std::string &item)
{
    _core.setLibGraph(_graphics[id].path);
}

void Menu::_selectScoreboard(std::size_t id, const std::string &item)
{
    _scoreboardIsOpen = true;
}

void Menu::_keySelect()
{
    static std::vector<void (Menu::*)(std::size_t, const std::string &)> actions = {
        &Menu::_selectGame,
        &Menu::_selectGraphLib,
        &Menu::_selectScoreboard
    };

    if (_currTab <= actions.size() - 1) {
        (this->*actions[_currTab])(_currItem, _items[_currTab][_currItem]);
    }
}

void Menu::_drawHelp()
{
    size_t posx = 25;

    _core.displayText(0, posx, 0, "ACTIONS");
    _core.displayText(0, posx, 2, "'F1'");
    _core.displayText(0, posx + 6, 2, "| Previous library");
    _core.displayText(0, posx, 3, "'F2'");
    _core.displayText(0, posx + 6, 3, "| Next library");
    _core.displayText(0, posx, 4, "'F3'");
    _core.displayText(0, posx + 6, 4, "| Previous game");
    _core.displayText(0, posx, 5, "'F4'");
    _core.displayText(0, posx + 6, 5, "| Next game");
    _core.displayText(0, posx, 6, "'F5'");
    _core.displayText(0, posx + 6, 6, "| Restart game");
    _core.displayText(0, posx, 7, "'F6'");
    _core.displayText(0, posx + 6, 7, "| Back to menu");
    _core.displayText(0, posx, 8, "'F7'");
    _core.displayText(0, posx + 6, 8, "| Exit");
}

void Menu::_drawNav()
{
    size_t posx = 0;
    size_t posy = 0;

    // Display tabs (beginning with the current tab)
    auto currTabIt = _tabs.begin() + _currTab;
    auto tabIt = currTabIt;
    while (tabIt != _tabs.end()) {
        _core.displayText(GameMenu::F_MENUS, posx, posy, *tabIt);
        posx += tabIt->length() + 1;
        ++tabIt;
    }
    tabIt = _tabs.begin();
    while (tabIt != currTabIt) {
        _core.displayText(GameMenu::F_MENUS, posx, posy, *tabIt);
        posx += tabIt->length() + 1;
        ++tabIt;
    }
}

void Menu::_drawTab()
{
    // Display items
    size_t posx = 2;
    size_t posy = 2;

    _core.displayImage(GameMenu::I_ARROW, 0.0f, (double)(posy + _currItem));
    for (const auto &item: _items[_currTab]) {
        _core.displayText(GameMenu::F_MENUS, posx, posy, item);
        ++posy;
    }
}

void Menu::_drawScoreboard()
{
    size_t posx = 0;
    size_t posy = 0;
    auto info = _scores[_currItem];

    _core.displayText(GameMenu::F_MENUS, posx, posy, "Scoreboard - " + info.gameName);
    posy += 2;
    for (const auto &item: info.scoreboard) {
        _core.displayText(GameMenu::F_MENUS, posx, posy, item.first.substr(0, 20));
        _core.displayText(GameMenu::F_MENUS, posx + 22, posy, std::to_string(item.second));
        ++posy;
    }
    posy += 1;
    _core.displayText(GameMenu::F_MENUS, posx, posy, "Press [ENTER] to return to menu");
}

void Menu::draw()
{
    if (_currTab == 2 && _scoreboardIsOpen) { // Scoreboard
        this->_drawScoreboard();
    } else {
        this->_drawHelp();
        this->_drawNav();
        this->_drawTab();
    }
}

void Menu::_pollMenuEvents()
{
    static const std::unordered_map<Key, void (Menu::*)()> handlers = {
        { Key::ENTER, &Menu::_keySelect },
        { Key::UP, &Menu::_keyPrevItem },
        { Key::DOWN, &Menu::_keyNextItem },
        { Key::LEFT, &Menu::_keyPrevTab },
        { Key::RIGHT, &Menu::_keyNextTab }
    };

    _core.getKeyboardEvents(_keyBindings);
    for (const auto &it : _keyBindings) {
        if (it.is_pressed)
            (this->*handlers.at(it.key))();
    }
}

void Menu::_pollScoreboardEvents()
{
    _core.getKeyboardEvents(_keyBindings);
    for (const auto &it : _keyBindings) {
        if (it.is_pressed && it.key == Key::ENTER)
            _scoreboardIsOpen = false;
    }
}

void Menu::pollEvents()
{
    if (_currTab == 2 && _scoreboardIsOpen) { // Scoreboard
        this->_pollScoreboardEvents();
    } else {
        this->_pollMenuEvents();
    }
}