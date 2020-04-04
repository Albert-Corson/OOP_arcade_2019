/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Scene
*/

#pragma once

#include <vector>
#include "GameMenu.hpp"
#include "core/ICore.hpp"

namespace arcade {
    class AScene {
        public:
            AScene() = delete;
            AScene(GameMenu &game, std::vector<KeyState> keyBindings)
                : _game(game)
                , _core(_game.getCore())
                , _keyBindings(keyBindings)
            {}
            virtual ~AScene() = default;

            virtual void draw() = 0;
            virtual void pollEvents() = 0;

        protected:
            GameMenu &_game;
            ICore &_core;
            std::vector<KeyState> _keyBindings;
    };
}