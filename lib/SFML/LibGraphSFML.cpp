/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibGraphSFML
*/

#include "LibGraphSFML.hpp"
#include "SFML/Window/Window.hpp"

LibGraphSFML::LibGraphSFML()
    : _window(nullptr)
{
}

LibGraphSFML::~LibGraphSFML()
{
}

void LibGraphSFML::createWindow(std::size_t width, std::size_t height)
{
    _winWidth = width;
    _winHeight = height;
    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height, 4), "Arcade");
}

void LibGraphSFML::render() const
{
    _window->display();
}
