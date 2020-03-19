/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "ICore.hpp"
#include "games/IGame.hpp"

#define LIBS_PATH   "./lib/"
#define GAMES_PATH  "./games/"

typedef ILibGraph *(*libLoader)();
typedef IGame *(*gameLoader)();

class Core : public ICore {
    public:
        Core();
        ~Core();
        ILibGraph *loadLib(const std::string name);
        IGame *loadGame(const std::string name);
        const std::vector<std::string> getLibsList() const;
        const std::vector<std::string> getGamesList() const;

    protected:
        std::unordered_map<std::string, ILibGraph *> _libs;
        std::unordered_map<std::string, IGame *> _games;
};