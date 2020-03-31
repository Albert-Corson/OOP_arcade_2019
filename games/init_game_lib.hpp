/*
** EPITECH PROJECT, 2019
** arcade
** File description:
** game lib init header
*/

#ifndef INIT_GAME_LIB_HPP_
#define INIT_GAME_LIB_HPP_

#include <memory>

#include "core/ICore.hpp"
#include "IGame.hpp"

extern "C" std::unique_ptr<arcade::IGame> init_game_lib(arcade::ICore& core);

#endif
