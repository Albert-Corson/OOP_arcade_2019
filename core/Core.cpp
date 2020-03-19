/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#include "Exception.hpp"
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
            _libs[std::string(LIBS_PATH) + (*libsIt)->d_name] = NULL;
        }
        ++libsIt;
    }
    while (*gamesIt != NULL) {
        if (ends_with((*gamesIt)->d_name, ".so")) {
            _games[std::string(GAMES_PATH) + (*gamesIt)->d_name] = NULL;
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

ILibGraph *Core::loadLib(const std::string path)
{
    if (_libs.find(path) != _libs.end()) {
        return (_libs[path]);
    }
    if (!ends_with(path, ".so")) {
        throw Exception(path + ": invalid file format");
    }
    DLLoader lib(path);
    libLoader getInstance = lib.getsym<libLoader>("getInstance");

    if (getInstance != NULL) {
        _libs[path] = getInstance();
        return (_libs[path]);
    }
    return (NULL);
}

IGame *Core::loadGame(const std::string path)
{
    if (_games.find(path) != _games.end()) {
        return (_games[path]);
    }
    if (!ends_with(path, ".so")) {
        throw Exception(path + ": invalid file format");
    }
    DLLoader game(path);
    gameLoader getInstance = game.getsym<gameLoader>("getInstance");

    if (getInstance != NULL) {
        _games[path] = getInstance();
        return (_games[path]);
    }
    return (NULL);
}