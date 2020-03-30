/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#include "Core.hpp"
#include "Clock.hpp"
#include "deps/DLLoader.hpp"
#include <filesystem>

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
    for (auto it : std::filesystem::directory_iterator(LIBS_PATH)) {
        if (ends_with(it.path().c_str(), ".so")) {
            _libsLoaders[it.path().c_str()] = NULL;
        }
    }
    for (auto it : std::filesystem::directory_iterator(GAMES_PATH)) {
        if (ends_with(it.path().c_str(), ".so")) {
            _gamesLoaders[it.path().c_str()] = NULL;
        }
    }
}

Core::~Core()
{
}

const std::vector<std::string> Core::getLibsList() const
{
    std::vector<std::string> keys;

    for (const auto &it : _libsLoaders) {
        keys.push_back(it.first);
    }
    return (keys);
}

const std::vector<std::string> Core::getGamesList() const
{
    std::vector<std::string> keys;

    for (const auto &it : _gamesLoaders) {
        keys.push_back(it.first);
    }
    return (keys);
}

void Core::loadLib(const std::string path)
{
    std::string rel_path = std::filesystem::path(path).lexically_normal().c_str();

    if (_libsLoaders.find(rel_path) != _libsLoaders.end() && _libsLoaders[rel_path] != nullptr) {
        _currLib = _libsLoaders[rel_path]();
        return;
    }
    DLLoader lib(rel_path);
    _libsLoaders[rel_path] = lib.getsym<libLoader>("init_graph_lib");

    if (_libsLoaders[rel_path] == NULL) {
        throw Exception(rel_path + ": cannot find symbol `init_game_lib`");
        return;
    }
    _currLib = _libsLoaders[rel_path]();
}

void Core::loadGame(const std::string path)
{
    std::string rel_path = std::filesystem::path(path).lexically_normal().c_str();

    if (_gamesLoaders.find(rel_path) != _gamesLoaders.end() && _gamesLoaders[rel_path] != nullptr) {
        _currGame = _gamesLoaders[rel_path]();
        return;
    }
    DLLoader game(rel_path);
    _gamesLoaders[rel_path] = game.getsym<gameLoader>("init_game_lib");

    if (_gamesLoaders[rel_path] == NULL) {
        throw Exception(rel_path + ": cannot find symbol `init_game_lib`");
        return;
    }
    _currGame = _gamesLoaders[rel_path]();
}

void Core::loadMenu(const std::string path)
{
    std::string rel_path = std::filesystem::path(path).lexically_normal().c_str();

    if (_currMenu != nullptr) {
        return;
    }
    DLLoader menu(rel_path);
    _menuLoader = menu.getsym<menuLoader>("init_menu_lib");

    if (_menuLoader == NULL) {
        throw Exception(rel_path + ": cannot find symbol `init_menu_lib`");
        return;
    }
    _currMenu = _menuLoader();
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

void Core::displayImage(int id, double posX, double posY)
{
    throw "TO DO";
}

void Core::displayText(int id, size_t posX, size_t posY, std::string const &text)
{
    throw "TO DO";
}

void Core::playAudio(int id, bool repeat)
{
    throw "TO DO";
}

void Core::stopAudio(int id)
{
    throw "TO DO";
}

void Core::clear()
{
    throw "TO DO";
}

void Core::render()
{
    throw "TO DO";
}

void Core::getKeyboardEvents(std::vector<KeyState> &keys)
{
    throw "TO DO";
}
