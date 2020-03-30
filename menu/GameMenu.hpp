/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** GameMenu
*/

#pragma once

#include "AGame.hpp"

namespace arcade {
    class ICore;

    class GameMenu: public AGame {
        public:
            GameMenu(ICore &core);
            ~GameMenu();

            void launch();
            void stop();
        
        protected:
            bool _running;
    };
}