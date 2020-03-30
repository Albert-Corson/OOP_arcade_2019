/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** main
*/

#include <memory>
#include "core/ICore.hpp"
#include "GameMenu.hpp"

extern "C" std::unique_ptr<arcade::IGame> init_menu_lib(arcade::ICore &core)
{
    return (std::make_unique<arcade::GameMenu>(core));
}