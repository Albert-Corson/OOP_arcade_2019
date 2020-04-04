/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** lib_communs
*/

#include "class/AScene.hpp"
#include "GameMenu.hpp"

std::string get_lib_name()
{
    return ("Menu");
}

std::unique_ptr<arcade::IGame> init_game_lib(arcade::ICore &core)
{
    return (std::make_unique<arcade::GameMenu>(core));
}