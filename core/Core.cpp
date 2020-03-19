/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#include "Core.hpp"
#include "DirIterator.hpp"
#include "DLLoader.hpp"

inline bool ends_with(const std::string &str, const std::string &end)
{
    if (end.size() > str.size()) {
        return (false);
    }
    return (std::equal(end.rbegin(), end.rend(), str.rbegin()));
}

Core::Core()
{
    DirIterator libsIt(LIBS_PATH);
    DirIterator gamesIt(GAMES_PATH);

    while (*libsIt != NULL) {
        if (ends_with((*libsIt)->d_name, ".so")) {
            _libs[(*libsIt)->d_name] = NULL;
        }
        ++libsIt;
    }
    while (*gamesIt != NULL) {
        if (ends_with((*gamesIt)->d_name, ".so")) {
            _games[(*gamesIt)->d_name] = NULL;
        }
        ++gamesIt;
    }
}

Core::~Core()
{
}

const std::vector<std::string> Core::getLibsList() const
{
    std::vector<std::string> keys;

    for (auto it: _libs) {
        keys.push_back(it.first);
    }
    return (keys);
}

const std::vector<std::string> Core::getGamesList() const
{
    std::vector<std::string> keys;

    for (auto it: _games) {
        keys.push_back(it.first);
    }
    return (keys);
}

ILibGraph *Core::loadLib(const std::string name)
{
    if (_libs.at(name) != NULL) {
        return (_libs.at(name));
    }
    DLLoader lib(name);
    libLoader getInstance = lib.getsym<libLoader>("getInstance");

    if (getInstance != NULL) {
        _libs[name] = getInstance();
        return (_libs[name]);
    }
    return (NULL);
}

IGame *Core::loadGame(const std::string name)
{
    if (_games.at(name) != NULL) {
        return (_games.at(name));
    }
    DLLoader game(GAMES_PATH + name);
    gameLoader getInstance = game.getsym<gameLoader>("getInstance");

    if (getInstance != NULL) {
        _games[name] = getInstance();
        return (_games[name]);
    }
    return (NULL);
}