/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibGraphLibcaca
*/

#include "LibGraphLibcaca.hpp"
#include "LibcacaKeys.hpp"
#include <fstream>
#include <sstream>
#include <cmath>

using namespace arcade;

LibGraphLibcaca::LibGraphLibcaca()
    : _display(caca_create_display(NULL))
{
    _canvas = _display ? caca_get_canvas(_display) : NULL;
    if (!_display || !_canvas)
        throw Exception("LibGraphLibcaca: could not create a display");
    caca_set_color_ansi(_canvas, CACA_WHITE, CACA_BLACK);
    caca_set_cursor(_display, 0);
}

LibGraphLibcaca::~LibGraphLibcaca()
{
    caca_free_display(_display);
}

void LibGraphLibcaca::getKeyboardEvents(std::vector<KeyState> &keysGame, std::vector<KeyState> &keysCore)
{
    caca_event_t ev;
    int key;
    Key current;

    for (auto &it : keysCore)
        it.is_pressed = false;
    for (auto &it : keysGame)
        it.is_pressed = false;
    while (caca_get_event(_display, CACA_EVENT_KEY_PRESS, &ev, 0)) {
        key = ev.data.key.ch;
        if (LIBCACA_KEYMAP.find(key) == LIBCACA_KEYMAP.end())
            continue;
        current = LIBCACA_KEYMAP.at(key);
        for (auto &it : keysGame) {
            if (it.key == current) {
                it.is_pressed = true;
                break;
            }
        }
        for (auto &it : keysCore) {
            if (it.key == current) {
                it.is_pressed = true;
                break;
            }
        }
    }
}

void LibGraphLibcaca::displayImage(int id, int posX, int posY)
{
    displayImage(id, static_cast<double>(posX), static_cast<double>(posY));
}

void LibGraphLibcaca::displayImage(int id, double posX, double posY)
{
    try {
        displayText(0, round(posX), round(posY), _images.at(id));
    } catch (...) {
        throw Exception("displayImage: incorrect id:" + std::to_string(id));
    }
}

void LibGraphLibcaca::displayText(int fontID, int posX, int posY, std::string const &text)
{
    caca_put_str(_canvas, posX * 2, posY, text.c_str());
}

void LibGraphLibcaca::clear()
{
    caca_clear_canvas(_canvas);
}

void LibGraphLibcaca::render()
{
    caca_refresh_display(_display);
}

void LibGraphLibcaca::loadResourceImage(int id, std::string const &filepathGraph, std::string const &filepathAscii)
{
    std::ifstream file(filepathAscii);
    std::stringstream buffer;

    if (!file.good())
        throw Exception("loadResourceImage: couldn't load file: " + filepathAscii);
    buffer << file.rdbuf();
    _images[id] = buffer.str();
}

void LibGraphLibcaca::resetResource()
{
    _images.clear();
}
