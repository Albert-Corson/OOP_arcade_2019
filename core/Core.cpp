/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#include <filesystem>
#include "Core.hpp"
#include "Clock.hpp"
#include "deps/DLLoader.hpp"

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
    for (auto it: std::filesystem::directory_iterator(LIBS_PATH)) {
        if (ends_with(it.path().c_str(), ".so")) {
            _libs[it.path().c_str()] = NULL;
        }
    }
    for (auto it: std::filesystem::directory_iterator(GAMES_PATH)) {
        if (ends_with(it.path().c_str(), ".so")) {
            _games[it.path().c_str()] = NULL;
        }
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
    std::string rel_path = std::filesystem::path(path).lexically_normal().c_str();

    if (_libs.find(rel_path) != _libs.end() && _libs[rel_path] != nullptr) {
        return (_libs[rel_path]);
    }
    DLLoader lib(rel_path);
    libLoader init_graph_lib = lib.getsym<libLoader>("init_graph_lib");

    if (init_graph_lib == NULL) {
        throw Exception(rel_path + ": cannot find symbol `init_game_lib`");
        return (_libs[rel_path]);
    }
    _libs[rel_path] = init_graph_lib();
    return (_libs[rel_path]);
}

std::unique_ptr<IGame> &Core::loadGame(const std::string path)
{
    std::string rel_path = std::filesystem::path(path).lexically_normal().c_str();

    if (_games.find(rel_path) != _games.end() && _games[rel_path] != nullptr) {
        return (_games[rel_path]);
    }
    DLLoader game(rel_path);
    gameLoader init_game_lib = game.getsym<gameLoader>("init_game_lib");

    if (init_game_lib == NULL) {
        throw Exception(rel_path + ": cannot find symbol `init_game_lib`");
        return (_games[rel_path]);
    }
    _games[rel_path] = init_game_lib();
    return (_games[rel_path]);
}

std::unique_ptr<IGame> &Core::loadMenu(const std::string path)
{
    std::string rel_path = std::filesystem::path(path).lexically_normal().c_str();

    if (_menu != nullptr) {
        return (_menu);
    }
    DLLoader menu(rel_path);
    gameLoader init_menu_lib = menu.getsym<menuLoader>("init_menu_lib");

    if (init_menu_lib == NULL) {
        throw Exception(rel_path + ": cannot find symbol `init_menu_lib`");
        return (_menu);
    }
    _menu = init_menu_lib();
    return (_menu);
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

void displayImage(int id, double posX, double posY)
{
    throw "TO DO";
}

void displayText(int id, size_t posX, size_t posY, std::string const &text)
{
    throw "TO DO";
}

void playAudio(int id, bool repeat = false)
{
    throw "TO DO";
}

void stopAudio(int id)
{
    throw "TO DO";
}

void clear()
{
    throw "TO DO";
}

void render()
{
    throw "TO DO";
}

void Core::getKeyboardEvents(std::vector<KeyState> &keys)
{
    throw "TO DO";
}
