/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** NcursesKeys
*/

#pragma once

#include "deps/keys.hpp"
#include <unordered_map>
#include <caca.h>

using namespace arcade;

#define NO_KEY -1

const std::unordered_map<int, Key> LIBCACA_KEYMAP = {
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

    { caca_key::CACA_KEY_ESCAPE , Key::ESCAPE },

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
    { CACA_KEY_RETURN, Key::ENTER },
    { CACA_KEY_BACKSPACE, Key::BACKSPACE },
    { CACA_KEY_TAB, Key::TAB },
    { CACA_KEY_PAGEUP, Key::PAGEUP },
    { CACA_KEY_PAGEDOWN, Key::PAGEDOWN },
    { CACA_KEY_END, Key::END },
    { CACA_KEY_HOME, Key::HOME },
    { CACA_KEY_INSERT, Key::INSERT },
    { CACA_KEY_DELETE, Key::DELETE },

    { '+', Key::ADD },
    { '-', Key::SUBTRACT },
    { '*', Key::MULTIPLY },
    { '/', Key::DIVIDE },

    { CACA_KEY_LEFT, Key::LEFT },
    { CACA_KEY_RIGHT, Key::RIGHT },
    { CACA_KEY_UP, Key::UP },
    { CACA_KEY_DOWN, Key::DOWN },

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
    { CACA_KEY_F1 , Key::F1 },
    { CACA_KEY_F2 , Key::F2 },
    { CACA_KEY_F3 , Key::F3 },
    { CACA_KEY_F4 , Key::F4 },
    { CACA_KEY_F5 , Key::F5 },
    { CACA_KEY_F6 , Key::F6 },
    { CACA_KEY_F7 , Key::F7 },
    { CACA_KEY_F8 , Key::F8 },
    { CACA_KEY_F9 , Key::F9 },
    { CACA_KEY_F10 , Key::F10 },
    { CACA_KEY_F11 , Key::F11 },
    { CACA_KEY_F12 , Key::F12 },
    { CACA_KEY_F13 , Key::F13 },
    { CACA_KEY_F14 , Key::F14 },
    { CACA_KEY_F15 , Key::F15 },
};
