/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibGraphSFML
*/

#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "LibGraphSFML.hpp"

using namespace arcade;

std::unique_ptr<ILibGraph> init_graph_lib()
{
    return (std::make_unique<LibGraphSFML>());
}

LibGraphSFML::LibGraphSFML()
{
    std::cout << "New instance of LibGraphSFML" << std::endl;
}

LibGraphSFML::~LibGraphSFML()
{
    std::cout << "Destroyed instance of LigGraphSFML" << std::endl;
}

void LibGraphSFML::getKeyboardEvents(std::vector<KeyState> &keysGame, std::vector<KeyState> &keysCore)
{
    throw "TO DO";
}

void LibGraphSFML::displayImage(int id, size_t posX, size_t posY)
{
    throw "TO DO";
}

void LibGraphSFML::displayImage(int id, double posX, double posY)
{
    throw "TO DO";
}

void LibGraphSFML::displayText(int id, size_t posX, size_t posY, std::string const &text)
{
    throw "TO DO";
}

void LibGraphSFML::playAudio(int id, bool repeat)
{
    throw "TO DO";
}

void LibGraphSFML::stopAudio(int id)
{
    throw "TO DO";
}

void LibGraphSFML::clear()
{
    throw "TO DO";
}

void LibGraphSFML::render()
{
    throw "TO DO";
}

void LibGraphSFML::loadResourceAudio(int id, std::string const &filepath)
{
    throw "TO DO";
}

void LibGraphSFML::loadResourceFont(int id, std::string const &filepath)
{
    throw "TO DO";
}

void LibGraphSFML::loadResourceImage(int id, std::string const &filepathGraph, std::string const &filepathAscii)
{
    throw "TO DO";
}

void LibGraphSFML::resetResource()
{
    throw "TO DO";
}
