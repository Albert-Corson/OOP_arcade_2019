/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibGraphNcurses
*/

#include "LibGraphNcurses.hpp"
#include "NcursesKeys.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <clocale>
#include <cmath>

using namespace arcade;

LibGraphNcurses::LibGraphNcurses()
{
    setlocale(LC_ALL, "");
    if (!initscr())
        throw Exception("LibGraphNcurses: could not initiate window");
    cbreak();
    noecho();
    nonl();
    nodelay(stdscr, true);
    intrflush(stdscr, true);
    keypad(stdscr, true);
    curs_set(0);
}

LibGraphNcurses::~LibGraphNcurses()
{
    endwin();
}

void LibGraphNcurses::getKeyboardEvents(std::vector<KeyState> &keysGame, std::vector<KeyState> &keysCore)
{
    Key current;

    for (auto &it: keysCore)
        it.is_pressed = false;
    for (auto &it: keysGame)
        it.is_pressed = false;
    for (int key = getch(); key != NO_KEY; key = getch()) {
        if (NCURSES_KEYMAP.find(key) == NCURSES_KEYMAP.end())
            continue;
        current = NCURSES_KEYMAP.at(key);
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

void LibGraphNcurses::displayImage(int id, int posX, int posY)
{
    displayImage(id, static_cast<double>(posX), static_cast<double>(posY));
}

void LibGraphNcurses::displayImage(int id, double posX, double posY)
{
    try {
        displayText(0, round(posX), round(posY), _images.at(id));
    } catch (...) {
        throw Exception("displayImage: incorrect id:" + std::to_string(id));
    }
}

void LibGraphNcurses::displayText(int fontID, int posX, int posY, std::string const &text)
{
    mvaddstr(posY, posX * 2, text.c_str());
}

void LibGraphNcurses::clear()
{
    erase();
}

void LibGraphNcurses::render()
{
    refresh();
}

void LibGraphNcurses::loadResourceImage(int id, std::string const &filepathGraph, std::string const &filepathAscii)
{
    std::ifstream file(filepathAscii);
    std::stringstream buffer;

    if (!file.good())
        throw LibGraphNcurses::Exception("loadResourceImage: couldn't load file: " + filepathAscii);
    buffer << file.rdbuf();
    _images[id] = buffer.str();
}

void LibGraphNcurses::resetResource()
{
    _images.clear();
}
