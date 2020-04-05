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
#include <time.h>

namespace arcade {
    typedef struct
    {
        int x;
        int y;
        char val;
        Key lastMove;
        double gap;
    }pos_t;

    class Game : public AGame {
        public:
            typedef void (Game::*keyAction_t)(Key, int);

            Game(ICore &core);
            ~Game() override = default;

            void launch() override final;

        private:
            void initAssets();
            void initMap();
            void initPacman();

            void resetGame();
            void sceneGame(std::unique_ptr<IClock> &cl, int &map);

            void changeMap(int &map);
            void processKeys(int &map);
            void pause(Key key = Key::UNKNOWN, int i = 0);

            void gameMotor();
            std::vector<Key> possibleDir(int i);
            Key dirEnemies(const std::vector<Key> &dirs, int id);
            Key originMove(int id);
            Key onlyOneKey();
            int getPos(int x, int y);
            std::vector<pos_t> getMap();
            void moveDown(Key key = Key::UNKNOWN, int i = 0);
            void moveUp(Key key = Key::UNKNOWN, int i = 0);
            void moveRight(Key key = Key::UNKNOWN, int i = 0);
            void moveLeft(Key key = Key::UNKNOWN, int i = 0);
            void movePlayers(const int x, const int y, const Key key, int i);
            void moveEnemies(const int x, const int y, const Key key, int i);
            void teleportation(int i);
            void eatFruit(void);
            void checkFruit(void);

            bool canMove(const size_t i, const Key dir);
            void displayAssets();
            void displayKeys(const int x, const int map);

            int _gameState;
            std::vector<KeyState> _actionKeys;
            std::unordered_map<Key, keyAction_t> _keyActions;
            std::vector<pos_t> _map;
            std::vector<pos_t> _players;
            int _currentMap;
    };
}
