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
    : _menuLoader(nullptr)
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
        _currLib.first = rel_path;
        _currLib.second = _libsLoaders[rel_path]();
        return;
    }
    DLLoader lib(rel_path);
    _libsLoaders[rel_path] = lib.getsym<libLoader>("init_graph_lib");

    if (_libsLoaders[rel_path] == NULL)
        throw Exception(rel_path + ": cannot find symbol `init_game_lib`");
    _currLib.first = rel_path;
    _currLib.second = _libsLoaders[rel_path]();
}

void Core::loadGame(const std::string path)
{
    std::string rel_path = std::filesystem::path(path).lexically_normal().c_str();

    if (_gamesLoaders.find(rel_path) != _gamesLoaders.end() && _gamesLoaders[rel_path] != nullptr) {
        _currGame.first = rel_path;
        _currGame.second = _gamesLoaders[rel_path](*this);
        return;
    }
    DLLoader game(rel_path);
    _gamesLoaders[rel_path] = game.getsym<gameLoader>("init_game_lib");

    if (_gamesLoaders[rel_path] == NULL)
        throw Exception(rel_path + ": cannot find symbol `init_game_lib`");
    _currGame.first = rel_path;
    _currGame.second = _gamesLoaders[rel_path](*this);
}

void Core::loadMenu(const std::string path)
{
    std::string rel_path = std::filesystem::path(path).lexically_normal().c_str();

    if (_menuLoader != nullptr) {
        _startMenu();
        return;
    }
    DLLoader menu(rel_path);
    _menuLoader = menu.getsym<menuLoader>("init_menu_lib");

    if (_menuLoader == NULL) {
        throw Exception(rel_path + ": cannot find symbol `init_menu_lib`");
    }
    _startMenu();
}

std::unique_ptr<IClock> Core::createClock()
{
    return (std::make_unique<Clock>());
}

void Core::loadResourceAudio(int id, std::string filepath)
{
    _resources.insert_or_assign(id, Resource(ResourceType::AUDIO, filepath, filepath));
}

void Core::loadResourceFont(int id, std::string filepath)
{
    _resources.insert_or_assign(id, Resource(ResourceType::FONT, filepath, filepath));
}

void Core::loadResourceImage(int id, std::string filepathGraph, std::string filepathAscii)
{
    _resources.insert_or_assign(id, Resource(ResourceType::IMG, filepathGraph, filepathAscii));
}

void Core::resetResource()
{
    _currLib.second->resetResource();
    _resources.clear();
}

void Core::displayImage(int id, int posX, int posY)
{
    _currLib.second->displayImage(id, posX, posY);
}

void Core::displayImage(int id, double posX, double posY)
{
    _currLib.second->displayImage(id, posX, posY);
}

void Core::displayText(int id, int posX, int posY, std::string const &text)
{
    _currLib.second->displayText(id, posX, posY, text);
}

void Core::playAudio(int id, bool repeat)
{
    _currLib.second->playAudio(id, repeat);
}

void Core::stopAudio(int id)
{
    _currLib.second->stopAudio(id);
}

void Core::clear()
{
    _currLib.second->clear();
}

void Core::render()
{
    _currLib.second->render();
}

void Core::getKeyboardEvents(std::vector<KeyState> &keys)
{
    static std::unordered_map<Key, keyAction> actions = {
        { Key::F9, &arcade::Core::_keyPrevGame },
        { Key::F10, &arcade::Core::_keyNextGame },
        { Key::F11, &arcade::Core::_keyPrevLib },
        { Key::F12, &arcade::Core::_keyNextLib },
        { Key::F5, &arcade::Core::_keyRestartGame },
        { Key::F1, &arcade::Core::_keyMenu },
        { Key::F4, &arcade::Core::_keyExit }
    };
    std::vector<KeyState> coreKeys = {
        KeyState(Key::F9),  // Previous game
        KeyState(Key::F10), // Next game
        KeyState(Key::F11), // Previous library
        KeyState(Key::F12), // Next library
        KeyState(Key::F5),  // Restart game
        KeyState(Key::F1),  // Go back to the menu
        KeyState(Key::F4)   // Exit
    };

    _currLib.second->getKeyboardEvents(keys, coreKeys);
    for (const auto &it : coreKeys) {
        if (it.is_pressed)
            (this->*actions[it.key])();
    }
}

void Core::_startMenu()
{
    if (!_menuLoader)
        throw Exception("_keyMenu: `_menuLoader` is no set");
    _currGame.first = "__MENU__";
    _currGame.second = _menuLoader(*this);
    _currGame.second->launch();
}

void Core::_keyPrevGame()
{
    bool find = false;
    auto it = _gamesLoaders.rbegin();

    for (; !find && it != _gamesLoaders.rend(); ++it) {
        if (it->first == _currGame.first)
            find = true;
    }
    if (it == _gamesLoaders.rend())
        it = _gamesLoaders.rbegin();
    else
        ++it;
    if (it == _gamesLoaders.rend())
        it = _gamesLoaders.rbegin();
    _currGame.first = it->first;
    _currGame.second = it->second(*this);
}

void Core::_keyNextGame()
{
    auto it = _gamesLoaders.find(_currGame.first);

    if (it == _gamesLoaders.end())
        it = _gamesLoaders.begin();
    else
        ++it;
    if (it == _gamesLoaders.end())
        it = _gamesLoaders.begin();
    _currGame.first = it->first;
    _currGame.second = it->second(*this);
}

void Core::_keyPrevLib()
{
    bool find = false;
    auto it = _libsLoaders.rbegin();

    for (; !find && it != _libsLoaders.rend(); ++it) {
        if (it->first == _currLib.first)
            find = true;
    }
    if (it == _libsLoaders.rend())
        it = _libsLoaders.rbegin();
    else
        ++it;
    if (it == _libsLoaders.rend())
        it = _libsLoaders.rbegin();
    _currLib.first = it->first;
    _currLib.second = it->second();
}

void Core::_keyNextLib()
{
    auto it = _libsLoaders.find(_currLib.first);

    if (it == _libsLoaders.end())
        it = _libsLoaders.begin();
    else
        ++it;
    if (it == _libsLoaders.end())
        it = _libsLoaders.begin();
    _currLib.first = it->first;
    _currLib.second = it->second();
}

void Core::_keyRestartGame()
{
    if (!_currGame.second)
        throw Exception("_keyRestartGame: an error occurred");
    _currLib.second->resetResource();
    _currGame.second = _gamesLoaders[_currGame.first](*this);
}

void Core::_keyMenu()
{
    if (!_menuLoader)
        throw Exception("_keyMenu: `_menuLoader` is no set");
    _currLib.second->resetResource();
    _startMenu();
}

void Core::_keyExit()
{
    _currGame.second->stop();
}
