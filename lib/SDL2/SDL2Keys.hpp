/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SDL2Keys
*/

#pragma once

#include "deps/keys.hpp"
#include <SDL2/SDL_keycode.h>
#include <unordered_map>

using namespace arcade;

#define NO_KEY -1

const std::unordered_map<SDL_Keycode, Key> SDL2_KEYMAP = {
    { 0, Key::UNKNOWN },
    { SDLK_a, Key::A },
    { SDLK_b, Key::B },
    { SDLK_c, Key::C },
    { SDLK_d, Key::D },
    { SDLK_e, Key::E },
    { SDLK_f, Key::F },
    { SDLK_g, Key::G },
    { SDLK_h, Key::H },
    { SDLK_i, Key::I },
    { SDLK_j, Key::J },
    { SDLK_k, Key::K },
    { SDLK_l, Key::L },
    { SDLK_m, Key::M },
    { SDLK_n, Key::N },
    { SDLK_o, Key::O },
    { SDLK_p, Key::P },
    { SDLK_q, Key::Q },
    { SDLK_r, Key::R },
    { SDLK_s, Key::S },
    { SDLK_t, Key::T },
    { SDLK_u, Key::U },
    { SDLK_v, Key::V },
    { SDLK_w, Key::W },
    { SDLK_x, Key::X },
    { SDLK_y, Key::Y },
    { SDLK_z, Key::Z },

    { SDLK_0, Key::NUM0 },
    { SDLK_1, Key::NUM1 },
    { SDLK_2, Key::NUM2 },
    { SDLK_3, Key::NUM3 },
    { SDLK_4, Key::NUM4 },
    { SDLK_5, Key::NUM5 },
    { SDLK_6, Key::NUM6 },
    { SDLK_7, Key::NUM7 },
    { SDLK_8, Key::NUM8 },
    { SDLK_9, Key::NUM9 },

    // { -1, Key::ESCAPE },
    // { -1, Key::LCONTROL },
    // { -1, Key::LSHIFT },
    // { -1, Key::LALT },
    // { -1, Key::LSYSTEM },
    // { -1, Key::RSHIFT },
    // { -1, Key::RALT },
    // { -1, Key::RSYSTEM },
    // { -1, Key::MENU },

    { SDLK_LEFTBRACKET, Key::LBRACKET },
    { SDLK_RIGHTBRACKET, Key::RBRACKET },
    { SDLK_SEMICOLON, Key::SEMICOLON },
    { SDLK_COMMA, Key::COMMA },
    { SDLK_PERIOD, Key::PERIOD },
    { SDLK_QUOTE, Key::QUOTE },
    { SDLK_SLASH, Key::SLASH },
    { SDLK_BACKSLASH, Key::BACKSLASH },
    // { -1, Key::TILDE },
    { SDLK_EQUALS, Key::EQUAL },
    { SDLK_MINUS, Key::HYPHEN },
    { SDLK_SPACE, Key::SPACE },

    { SDLK_RETURN, Key::ENTER },
    { SDLK_BACKSPACE, Key::BACKSPACE },
    { SDLK_TAB, Key::TAB },
    { SDLK_PAGEUP, Key::PAGEUP },
    { SDLK_PAGEDOWN, Key::PAGEDOWN },
    { SDLK_END, Key::END },
    { SDLK_HOME, Key::HOME },
    { SDLK_INSERT, Key::INSERT },
    { SDLK_DELETE, Key::DELETE },

    // { -1, Key::ADD },
    // { -1, Key::SUBTRACT },
    // { -1, Key::MULTIPLY },
    // { -1, Key::DIVIDE },

    { SDLK_LEFT, Key::LEFT },
    { SDLK_RIGHT, Key::RIGHT },
    { SDLK_UP, Key::UP },
    { SDLK_DOWN, Key::DOWN },
    { SDLK_0, Key::NUMPAD0 },
    { SDLK_1, Key::NUMPAD1 },
    { SDLK_2, Key::NUMPAD2 },
    { SDLK_3, Key::NUMPAD3 },
    { SDLK_4, Key::NUMPAD4 },
    { SDLK_5, Key::NUMPAD5 },
    { SDLK_6, Key::NUMPAD6 },
    { SDLK_7, Key::NUMPAD7 },
    { SDLK_8, Key::NUMPAD8 },
    { SDLK_9, Key::NUMPAD9 },
    { SDLK_F1, Key::F1 },
    { SDLK_F2, Key::F2 },
    { SDLK_F3, Key::F3 },
    { SDLK_F4, Key::F4 },
    { SDLK_F5, Key::F5 },
    { SDLK_F6, Key::F6 },
    { SDLK_F7, Key::F7 },
    { SDLK_F8, Key::F8 },
    { SDLK_F9, Key::F9 },
    { SDLK_F10, Key::F10 },
    { SDLK_F11, Key::F11 },
    { SDLK_F12, Key::F12 },
    { SDLK_F13, Key::F13 },
    { SDLK_F14, Key::F14 },
    { SDLK_F15, Key::F15 }
};
