/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#include "Exception.hpp"
#include "Core.hpp"
#include "Clock.hpp"
#include "deps/DirIterator.hpp"
#include "deps/DLLoader.hpp"
#include "deps/Path.hpp"

using namespace arcade;

static inline bool ends_with(const std::string &str, const std::string &end)
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

    for (const auto &it: _libs) {
        keys.push_back(it.first);
    }
    return (keys);
}

const std::vector<std::string> Core::getGamesList() const
{
    std::vector<std::string> keys;

    for (const auto &it: _games) {
        keys.push_back(it.first);
    }
    return (keys);
}

std::unique_ptr<ILibGraph> &Core::loadLib(const std::string path)
{
    std::string rel_path = fs::Path(path).lexically_normal().c_str();

    if (_libs.find(rel_path) != _libs.end() && _libs[rel_path] != nullptr) {
        return (_libs[rel_path]);
    }
    if (!ends_with(rel_path, ".so")) {
        throw Exception(rel_path + ": invalid file format");
    }
    DLLoader lib(rel_path);
    libLoader getInstance = lib.getsym<libLoader>("getInstance");

    if (getInstance != NULL) {
        _libs[rel_path] = getInstance();
    }
    return (_libs[rel_path]);
}

std::unique_ptr<IGame> &Core::loadGame(const std::string path)
{
    std::string rel_path = fs::Path(path).lexically_normal().c_str();

    if (_games.find(rel_path) != _games.end() && _games[rel_path] != nullptr) {
        return (_games[rel_path]);
    }
    if (!ends_with(rel_path, ".so")) {
        throw Exception(rel_path + ": invalid file format");
    }
    DLLoader game(rel_path);
    gameLoader getInstance = game.getsym<gameLoader>("getInstance");

    if (getInstance != NULL) {
        _games[rel_path] = getInstance();
    }
    return (_games[rel_path]);
}

std::unique_ptr<IClock> Core::createClock()
{
    return (std::make_unique<Clock>());
}

void Core::loadResourceAudio(int id, std::string filepath)
{
    throw "TO DO";
}

void Core::loadResourceFont(int id, std::string filepath)
{
    throw "TO DO";
}

void Core::loadResourceImage(int id, std::string filepathGraph, std::string filepathAscii)
{
    throw "TO DO";
}

void Core::resetResource()
{
    throw "TO DO";
}

void Core::displayImage(int id, size_t posX, size_t posY)
{
    throw "TO DO";
}

void Core::getKeyboardEvents(std::vector<KeyState> &keys)
{
    throw "TO DO";
}
