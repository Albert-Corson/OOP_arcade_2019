/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibGraphNcurses
*/

#include <memory>
#include <iostream>
#include "LibGraphNcurses.hpp"

using namespace arcade;

std::unique_ptr<ILibGraph> init_graph_lib()
{
    return (std::make_unique<LibGraphNcurses>());
}

LibGraphNcurses::LibGraphNcurses()
{
    std::cout << "New instance of LibGraphNcurses" << std::endl;
}

LibGraphNcurses::~LibGraphNcurses()
{
    std::cout << "Destroyed instance of LigGraphSFML" << std::endl;
}

void LibGraphNcurses::getKeyboardEvents(std::vector<KeyState> &keysGame, std::vector<KeyState> &keysCore)
{
    throw "TO DO";
}

void LibGraphNcurses::displayImage(int id, size_t posX, size_t posY)
{
    throw "TO DO";
}

void LibGraphNcurses::displayImage(int id, double posX, double posY)
{
    throw "TO DO";
}

void LibGraphNcurses::displayText(int id, size_t posX, size_t posY, std::string const &text)
{
    throw "TO DO";
}

void LibGraphNcurses::playAudio(int id, bool repeat)
{
    throw "TO DO";
}

void LibGraphNcurses::stopAudio(int id)
{
    throw "TO DO";
}

void LibGraphNcurses::clear()
{
    throw "TO DO";
}

void LibGraphNcurses::render()
{
    throw "TO DO";
}

void LibGraphNcurses::loadResourceAudio(int id, std::string const &filepath)
{
    throw "TO DO";
}

void LibGraphNcurses::loadResourceFont(int id, std::string const &filepath)
{
    throw "TO DO";
}

void LibGraphNcurses::loadResourceImage(int id, std::string const &filepathGraph, std::string const &filepathAscii)
{
    throw "TO DO";
}

void LibGraphNcurses::resetResource()
{
    throw "TO DO";
}
