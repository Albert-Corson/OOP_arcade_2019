/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** NcursesKeys
*/

#pragma once

#include "deps/keys.hpp"
#include <ncurses.h>
#include <unordered_map>

using namespace arcade;

#define NO_KEY -1

const std::unordered_map<int, Key> NCURSES_KEYMAP = {
    { 0, Key::UNKNOWN },
    { 'a', Key::A },
    { 'b', Key::B },
    { 'c', Key::C },
    { 'd', Key::D },
    { 'e', Key::E },
    { 'f', Key::F },
    { 'g', Key::G },
    { 'h', Key::H },
    { 'i', Key::I },
    { 'j', Key::J },
    { 'k', Key::K },
    { 'l', Key::L },
    { 'm', Key::M },
    { 'n', Key::N },
    { 'o', Key::O },
    { 'p', Key::P },
    { 'q', Key::Q },
    { 'r', Key::R },
    { 's', Key::S },
    { 't', Key::T },
    { 'u', Key::U },
    { 'v', Key::V },
    { 'w', Key::W },
    { 'x', Key::X },
    { 'y', Key::Y },
    { 'z', Key::Z },

    { '0', Key::NUM0 },
    { '1', Key::NUM1 },
    { '2', Key::NUM2 },
    { '3', Key::NUM3 },
    { '4', Key::NUM4 },
    { '5', Key::NUM5 },
    { '6', Key::NUM6 },
    { '7', Key::NUM7 },
    { '8', Key::NUM8 },
    { '9', Key::NUM9 },

    // { -1, Key::ESCAPE },
    // { -1, Key::LCONTROL },
    // { -1, Key::LSHIFT },
    // { -1, Key::LALT },
    // { -1, Key::LSYSTEM },
    // { -1, Key::RSHIFT },
    // { -1, Key::RALT },
    // { -1, Key::RSYSTEM },
    // { -1, Key::MENU },

    { '[', Key::LBRACKET },
    { ']', Key::RBRACKET },
    { ';', Key::SEMICOLON },
    { ',', Key::COMMA },
    { '.', Key::PERIOD },
    { '\'', Key::QUOTE },
    { '/', Key::SLASH },
    { '\\', Key::BACKSLASH },
    { '~', Key::TILDE },
    { '=', Key::EQUAL },
    { '-', Key::HYPHEN },
    { ' ', Key::SPACE },

    { '\r', Key::ENTER },
    { '\n', Key::ENTER },
    { KEY_BACKSPACE, Key::BACKSPACE },
    { '\t', Key::TAB },
    { KEY_PPAGE, Key::PAGEUP },
    { KEY_NPAGE, Key::PAGEDOWN },
    { KEY_END, Key::END },
    { KEY_HOME, Key::HOME },
    { KEY_IC, Key::INSERT },
    { KEY_DC, Key::DELETE },

    // { -1, Key::ADD },
    // { -1, Key::SUBTRACT },
    // { -1, Key::MULTIPLY },
    // { -1, Key::DIVIDE },

    { KEY_LEFT, Key::LEFT },
    { KEY_RIGHT, Key::RIGHT },
    { KEY_UP, Key::UP },
    { KEY_DOWN, Key::DOWN },
    { '0', Key::NUMPAD0 },
    { '1', Key::NUMPAD1 },
    { '2', Key::NUMPAD2 },
    { '3', Key::NUMPAD3 },
    { '4', Key::NUMPAD4 },
    { '5', Key::NUMPAD5 },
    { '6', Key::NUMPAD6 },
    { '7', Key::NUMPAD7 },
    { '8', Key::NUMPAD8 },
    { '9', Key::NUMPAD9 },
    { KEY_F(1), Key::F1 },
    { KEY_F(2), Key::F2 },
    { KEY_F(3), Key::F3 },
    { KEY_F(4), Key::F4 },
    { KEY_F(5), Key::F5 },
    { KEY_F(6), Key::F6 },
    { KEY_F(7), Key::F7 },
    { KEY_F(8), Key::F8 },
    { KEY_F(9), Key::F9 },
    { KEY_F(10), Key::F10 },
    { KEY_F(11), Key::F11 },
    { KEY_F(12), Key::F12 },
    { KEY_F(13), Key::F13 },
    { KEY_F(14), Key::F14 },
    { KEY_F(15), Key::F15 },
};
