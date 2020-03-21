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
#include <memory>
#include "ICore.hpp"
#include "games/IGame.hpp"

#define LIBS_PATH   "lib/"
#define GAMES_PATH  "games/"

typedef std::unique_ptr<ILibGraph> (*libLoader)();
typedef std::unique_ptr<IGame> (*gameLoader)();

class Core : public ICore {
    public:
        Core();
        ~Core();
        std::unique_ptr<ILibGraph> &loadLib(const std::string name);
        std::unique_ptr<IGame> &loadGame(const std::string name);
        const std::vector<std::string> getLibsList() const;
        const std::vector<std::string> getGamesList() const;

    protected:
        std::unordered_map<std::string, std::unique_ptr<ILibGraph>> _libs;
        std::unordered_map<std::string, std::unique_ptr<IGame>> _games;
};