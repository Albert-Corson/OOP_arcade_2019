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

        private:
            enum RFont {
                F_MENUS
            };
            enum RImage {
                I_ARROW
            };

            typedef void (GameMenu::*keyAction)();
            bool _running{false};
            int _currTab{0};
            int _currItem{0};

            void _drawMenu();
            void _handleEvents();
            void _keyNextTab();
            void _keyPrevTab();
            void _keyNextItem();
            void _keyPrevItem();
            void _keySelect();
    };
}