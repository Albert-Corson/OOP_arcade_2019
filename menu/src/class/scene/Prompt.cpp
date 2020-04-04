/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Prompt
*/

#include "class/scene/Prompt.hpp"

using namespace arcade;

Prompt::Prompt(GameMenu &game)
    : AScene(game, {
        Key::ENTER,
        Key::BACKSPACE,
        Key::A,
        Key::B,
        Key::C,
        Key::D,
        Key::E,
        Key::F,
        Key::G,
        Key::H,
        Key::I,
        Key::J,
        Key::K,
        Key::L,
        Key::M,
        Key::N,
        Key::O,
        Key::P,
        Key::Q,
        Key::R,
        Key::S,
        Key::T,
        Key::U,
        Key::V,
        Key::W,
        Key::X,
        Key::Y,
        Key::Z
    })
{}

void Prompt::draw()
{
    _core.displayText(GameMenu::F_MENUS, 1, 1, "Enter a username:");
    _core.displayText(GameMenu::F_MENUS, 1, 2, "> " + _username);
    _core.displayText(GameMenu::F_MENUS, 1, 4, "Press [ENTER] to confirm");
}

void Prompt::pollEvents()
{
    _core.getKeyboardEvents(_keyBindings);
    for (const auto &it : _keyBindings) {
        if (it.is_pressed) {
            if (it.key == Key::ENTER) {
                _confirm();
            } else {
                _type(it.key);
            }
        }
    }
}

void Prompt::_confirm()
{
    _core.setUserName(_username);
    _game.setScene(GameMenu::S_MENU);
}

void Prompt::_type(const Key key)
{
    if (key == Key::BACKSPACE) {
        if (_username.length() > 0)
            _username.pop_back();
    } else {
        _username.push_back('A' + key);
    }
}