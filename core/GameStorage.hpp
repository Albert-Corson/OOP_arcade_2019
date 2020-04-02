/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** GameStorage
*/

#pragma once

#include "Core.hpp"

namespace arcade {
    struct Core::GameStorage : public ICore::LibInfo {
        GameStorage(const std::string &libPath = "", const std::string &libName = "", const gameLoader_t &libLoader = nullptr);
        GameStorage(const GameStorage &other);
        GameStorage &operator=(const GameStorage &other);

        void loadScoreboard();
        void dumpScoreboard() const;
        void updateScoreboardEntry(const std::string &userName, unsigned long score);
        const ICore::GameScoreboard getSortedScoreboard() const;

        gameLoader_t loader;
        std::unique_ptr<IGame> instance;

        std::unordered_map<std::string, unsigned long> scoreboard;
    };
}