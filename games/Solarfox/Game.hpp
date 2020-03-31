/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Game
*/

#pragma once

#include "AGame.hpp"
#include <unordered_map>

namespace arcade {
    class Game : public AGame {
        public:
            typedef void (Game::*keyAction_t)(Key);

            Game(ICore &core);
            ~Game() = default;

            void launch() override final;

        private:
            void processKeys();
            void setPlayerDir(Key key);
            void playerShoot(Key key = Key::UNKNOWN);
            void pause(Key key = Key::UNKNOWN);

            bool _paused;
            std::vector<KeyState> _actionKeys;
            std::unordered_map<Key, keyAction_t> _keyActions;
    };

}