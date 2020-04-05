/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Game
*/

#pragma once

#include "AGame.hpp"
#include <time.h>
#include <unordered_map>

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
            void initAssets();
            void initMap();
            void initSnake();

            void sceneGame(std::unique_ptr<IClock> &cl, double &idx);

            void processKeys(double &idx);
            void pause(Key key = Key::UNKNOWN);

            void gameMotor();
            Key onlyOneKey();
            int getPos(int x, int y);
            std::vector<pos_t> getMap();
            void moveDown(Key key = Key::UNKNOWN);
            void moveUp(Key key = Key::UNKNOWN);
            void moveRight(Key key = Key::UNKNOWN);
            void moveLeft(Key key = Key::UNKNOWN);
            void moveSnake(const int x, const int y, const Key key);
            void moveTail(void);
            void eatFruit(void);
            void newFruit(void);

            bool canMove();
            void displayAssets(double idx);
            Key snakeDirection(size_t i);
            void displayKeys(const int x);

            int _gameState;
            std::vector<KeyState> _actionKeys;
            std::unordered_map<Key, keyAction_t> _keyActions;
            std::vector<pos_t> _map;
            std::vector<pos_t> _snake;
            Key _lastKey;
    };
}
