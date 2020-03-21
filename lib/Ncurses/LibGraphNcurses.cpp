/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibGraphNcurses
*/

#include <memory>
#include <iostream>
#include "LibGraphNcurses.hpp"

LibGraphNcurses::LibGraphNcurses()
{
    std::cout << "New instance of LibGraphNcurses" << std::endl;
}

LibGraphNcurses::~LibGraphNcurses()
{
    std::cout << "Destroyed instance of LigGraphSFML" << std::endl;
}

std::unique_ptr<ILibGraph> getInstance()
{
    return (std::make_unique<LibGraphNcurses>());
}