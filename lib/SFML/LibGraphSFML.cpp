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

LibGraphSFML::LibGraphSFML()
{
    std::cout << "New instance of LibGraphSFML" << std::endl;
}

LibGraphSFML::~LibGraphSFML()
{
    std::cout << "Destroyed instance of LigGraphSFML" << std::endl;
}

std::unique_ptr<ILibGraph> getInstance()
{
    return (std::make_unique<LibGraphSFML>());
}