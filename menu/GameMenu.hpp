/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** GameMenu
*/

#pragma once

#include "AGame.hpp"

namespace arcade {
    class GameMenu: public AGame {
        public:
            GameMenu();
            ~GameMenu();

            void launch();
            void stop();

        private:
            
    };
}