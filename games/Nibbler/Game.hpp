/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Game
*/

#pragma once

#include "AGame.hpp"

namespace arcade {
    class Game : public AGame {
        public:
            typedef void (Game::*keyAction_t)(Key);

            Game(ICore &core);
            ~Game() = default;

            void launch() override final;
    };
}