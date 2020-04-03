/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Game
*/

#pragma once

#include "AGame.hpp"
#include <unordered_map>
#include <fstream>

namespace arcade {
    typedef struct
    {
        int x;
        int y;
        char val;
    }pos_t;

    class Game : public AGame {
        public:
            typedef void (Game::*keyAction_t)(Key);

            Game(ICore &core);
            ~Game() override = default;

            void launch() override final;

        private:
            void processKeys();
            void pause(Key key = Key::UNKNOWN);

            void initAssets();
            void displayAssets(double idx);
            Key snakeDirection(size_t i);
            bool canMove();

            void gameMotor();
            Key onlyOneKey();
            void initMap(void);
            void initSnake(const char id);
            int getPos(int x, int y);
            std::vector<pos_t> getMap();
            void moveSnake(const int x, const int y, const Key key);
            void moveDown(Key key = Key::UNKNOWN);
            void moveUp(Key key = Key::UNKNOWN);
            void moveRight(Key key = Key::UNKNOWN);
            void moveLeft(Key key = Key::UNKNOWN);
            void moveTail(void);
            void eatFruit(void);
            void checkFruit(void);

            int _gameState;
            std::vector<KeyState> _actionKeys;
            std::unordered_map<Key, keyAction_t> _keyActions;
            std::vector<pos_t> _map;
            std::vector<pos_t> _snake;
            Key _lastKey;
    };
}
