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
            typedef void (GameMenu::*keyAction_t)();

            GameMenu(ICore &core);
            ~GameMenu();

            void launch() override final;

        private:
            enum RFont {
                F_MENUS
            };
            enum RImage {
                I_ARROW
            };

            std::vector<KeyState> _actionKeys;
            std::unordered_map<Key, keyAction_t> _keyActions;

            std::size_t _currTab;
            std::size_t _currItem;
            const std::vector<std::string> _tabs;
            const std::vector<std::vector<ICore::LibInfo>> _items;

            void _drawMenu();
            void _handleEvents();
            void _keyNextTab();
            void _keyPrevTab();
            void _keyNextItem();
            void _keyPrevItem();
            void _keySelect();
    };
}
