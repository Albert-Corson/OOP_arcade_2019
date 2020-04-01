/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** GameStorage
*/

#include "GameStorage.hpp"
#include <fstream>

using namespace arcade;

Core::GameStorage::GameStorage(const std::string &libPath, const std::string &libName, const gameLoader_t &libLoader)
    : LibInfo(libPath, libName)
    , loader(libLoader)
    , instance(nullptr)
{
}

Core::GameStorage::GameStorage(const Core::GameStorage &other)
    : LibInfo(other)
    , loader(other.loader)
    , instance(nullptr)
{
}

Core::GameStorage &Core::GameStorage::operator=(const Core::GameStorage &other)
{
    LibInfo::operator=(other);
    this->loader = other.loader;
    this->instance = nullptr;
    return (*this);
}

void Core::GameStorage::loadScoreboard() 
{
    std::ifstream file(path + ".score");
    std::string line;
    unsigned long score = 0;
    std::string username;
    std::size_t offset = 0;

    if (!file)
        return;
    std::getline(file, line);
    while (!file.eof()) {
        offset = 0;
        while (line[offset] >= '0' && line[offset] <= '9')
            ++offset;
        score = std::stoul(line);
        username = line.substr(offset + 1);
        scoreboard[username] = score;
    }
}

void Core::GameStorage::dumpScoreboard() const
{
    std::ofstream file(path + ".score");

    if (!file)
        throw Core::Exception("GameStorage::dumpScoreboard: couldn't create/open output file");
    file << "[" + name + "]" << std::endl;
    for (const auto &it : scoreboard)
        file << it.second << " " << it.first << std::endl;
}

void Core::GameStorage::updateScoreboardEntry(const std::string &userName, unsigned long score) 
{
    unsigned long &entry = scoreboard[userName];

    if (entry < score)
        entry = score;
}
