/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** GameMenu
*/

#pragma once

#include "AGame.hpp"

namespace arcade {
    class AScene;

    class GameMenu : public AGame {
        public:
            GameMenu(ICore &core);
            ~GameMenu() override = default;

            void launch() override final;

            ICore &getCore() const;

            enum E_RFont {
                F_MENUS
            };
            enum E_RImage {
                I_ARROW
            };

            enum E_Scene {
                S_PROMPT,
                S_MENU
            };

            void setScene(const E_Scene);

        private:
            std::size_t _currScene;
            std::vector<std::unique_ptr<AScene>> _scenes;
    };
}
