/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** lib_communs
*/

#include "LibGraphSFML.hpp"

std::string get_lib_name()
{
    return ("SFML");
}

std::unique_ptr<arcade::ILibGraph> init_graph_lib()
{
    return (std::make_unique<arcade::LibGraphSFML>());
}