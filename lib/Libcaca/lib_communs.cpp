/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** lib_communs
*/

#include "LibGraphLibcaca.hpp"

std::string get_lib_name()
{
    return ("Libcaca");
}

std::unique_ptr<arcade::ILibGraph> init_graph_lib()
{
    return (std::make_unique<arcade::LibGraphLibcaca>());
}