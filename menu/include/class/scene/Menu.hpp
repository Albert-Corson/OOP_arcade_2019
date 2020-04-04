/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Menu
*/

#pragma once

#include "class/AScene.hpp"

namespace arcade {
    class Menu : public AScene {
        public:
            Menu(GameMenu &game);
            ~Menu() override = default;

            void draw() final;
            void pollEvents() final;

        private:
            void _drawNav();
            void _drawTab();
            void _drawScoreboard();

            void _pollMenuEvents();
            void _pollScoreboardEvents();

            void _selectGame(std::size_t id, const std::string &item);
            void _selectGraphLib(std::size_t id, const std::string &item);
            void _selectScoreboard(std::size_t id, const std::string &item);

            void _keyNextItem();
            void _keyPrevItem();
            void _keyNextTab();
            void _keyPrevTab();
            void _keySelect();

            const std::vector<std::string> _tabs;
            size_t _currTab;
            std::vector<std::vector<std::string>> _items;
            size_t _currItem;
            const std::vector<ICore::LibInfo> _games;
            const std::vector<ICore::LibInfo> _graphics;
            const std::vector<ICore::GameScoreboard> _scores;
            bool _scoreboardIsOpen{false};
    };
}