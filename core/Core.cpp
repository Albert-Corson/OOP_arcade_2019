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

Core::Core(const std::string &menuToLoad)
    : _menuLoader(nullptr)
{
    std::string path;
    std::string name;

    _loadMenu(menuToLoad);
    for (auto it : std::filesystem::directory_iterator(LIBGRAPHS_PATH)) {
        if (ends_with(it.path().c_str(), ".so"))
            _loadLibGraph(it.path().c_str());
    }
    for (auto it : std::filesystem::directory_iterator(GAMES_PATH)) {
        if (ends_with(it.path().c_str(), ".so"))
            _loadGame(it.path().c_str());
    }
}

Core::~Core()
{
}

const std::vector<ICore::LibInfo> Core::getLibGraphsList() const
{
    std::vector<LibInfo> keys;

    for (const auto &it : _libGraphsInfos) {
        keys.push_back(LibInfo(it.path, it.name));
    }
    return (keys);
}

const std::vector<ICore::LibInfo> Core::getGamesList() const
{
    std::vector<LibInfo> keys;

    for (const auto &it : _gamesInfos) {
        keys.push_back(LibInfo(it.path, it.name));
    }
    return (keys);
}

void Core::setLibGraph(const std::string path)
{
    bool find = false;

    for (const auto &it : _libGraphsInfos) {
        if (it.path == path) {
            find = true;
            _currLib.first = path;
            _currLib.second = it.loader();
            break;
        }
    }
    if (!find)
        throw Core::Exception("setLibGraph: no such lib: " + path);
}

void Core::setGame(const std::string path)
{
    bool find = false;

    for (const auto &it : _gamesInfos) {
        if (it.path == path) {
            find = true;
            _currGame.first = path;
            _currGame.second = it.loader(*this);
            break;
        }
    }
    if (!find)
        throw Core::Exception("setGame: no such lib: " + path);
}

void Core::startMenu()
{
    if (!_menuLoader)
        throw Exception("_keyMenu: `_menuLoader` is no set");
    resetResource();
    _currGame.first = "__MENU__";
    _currGame.second = _menuLoader(*this);
    _currGame.second->launch();
}

std::unique_ptr<IClock> Core::createClock()
{
    return (std::make_unique<Clock>());
}

void Core::loadResourceAudio(int id, std::string filepath)
{
    _resources.insert_or_assign(id, Resource(ResourceType::AUDIO, filepath, filepath));
    _currLib.second->loadResourceAudio(id, filepath);
}

void Core::loadResourceFont(int id, std::string filepath)
{
    _resources.insert_or_assign(id, Resource(ResourceType::FONT, filepath, filepath));
    _currLib.second->loadResourceFont(id, filepath);
}

void Core::loadResourceImage(int id, std::string filepathGraph, std::string filepathAscii)
{
    _resources.insert_or_assign(id, Resource(ResourceType::IMG, filepathGraph, filepathAscii));
    _currLib.second->loadResourceImage(id, filepathGraph, filepathAscii);
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

void Core::_loadLibGraph(const std::string path)
{
    std::string rel_path = std::filesystem::path(path).lexically_normal().c_str();
    libNameGetter nameGetter = nullptr;
    libGraphLoader loader = nullptr;

    DLLoader lib(rel_path);
    loader = lib.getsym<libGraphLoader>("init_graph_lib");
    nameGetter = lib.getsym<libNameGetter>("get_lib_name");
    if (!loader || !nameGetter)
        throw Exception(rel_path + " isn't valid");
    _libGraphsInfos.push_back(LibGraphInfo(rel_path, nameGetter(), loader));
}

void Core::_loadGame(const std::string path)
{
    std::string rel_path = std::filesystem::path(path).lexically_normal().c_str();
    libNameGetter nameGetter = nullptr;
    gameLoader loader = nullptr;

    DLLoader lib(rel_path);
    loader = lib.getsym<gameLoader>("init_game_lib");
    nameGetter = lib.getsym<libNameGetter>("get_lib_name");
    if (!loader || !nameGetter)
        throw Exception(rel_path + " isn't valid");
    _gamesInfos.push_back(GameInfo(rel_path, nameGetter(), loader));
}

void Core::_loadMenu(const std::string path)
{
    std::string rel_path = std::filesystem::path(path).lexically_normal().c_str();
    DLLoader menu(rel_path);

    _menuLoader = menu.getsym<menuLoader>("init_menu_lib");
    if (_menuLoader == NULL)
        throw Exception(rel_path + ": cannot find symbol `init_menu_lib`");
}

void Core::_keyPrevGame()
{
    auto it = _gamesInfos.rbegin();

    for (; it != _gamesInfos.rend(); ++it) {
        if (it->path == _currGame.first)
            break;
    }
    if (it == _gamesInfos.rend())
        it = _gamesInfos.rbegin();
    else
        ++it;
    if (it == _gamesInfos.rend())
        it = _gamesInfos.rbegin();
    _currGame.first = it->path;
    _currGame.second = it->loader(*this);
}

void Core::_keyNextGame()
{
    auto it = _gamesInfos.begin();

    for (; it != _gamesInfos.end(); ++it) {
        if (it->path == _currGame.first)
            break;
    }
    if (it == _gamesInfos.end())
        it = _gamesInfos.begin();
    else
        ++it;
    if (it == _gamesInfos.end())
        it = _gamesInfos.begin();
    _currGame.first = it->path;
    _currGame.second = it->loader(*this);
}

void Core::_keyPrevLib()
{
    auto it = _libGraphsInfos.rbegin();

    for (; it != _libGraphsInfos.rend(); ++it) {
        if (it->path == _currLib.first)
            break;
    }
    if (it == _libGraphsInfos.rend())
        it = _libGraphsInfos.rbegin();
    else
        ++it;
    if (it == _libGraphsInfos.rend())
        it = _libGraphsInfos.rbegin();
    _currLib.first = it->path;
    _currLib.second = it->loader();
}

void Core::_keyNextLib()
{
    auto it = _libGraphsInfos.begin();

    for (; it != _libGraphsInfos.end(); ++it) {
        if (it->path == _currLib.first)
            break;
    }
    if (it == _libGraphsInfos.end())
        it = _libGraphsInfos.begin();
    else
        ++it;
    if (it == _libGraphsInfos.end())
        it = _libGraphsInfos.begin();
    _currLib.first = it->path;
    _currLib.second = it->loader();
}

void Core::_keyRestartGame()
{
    for (const auto &it : _gamesInfos) {
        if (it.path == _currGame.first) {
            resetResource();
            _currGame.second = it.loader(*this);
            return;
        }
    }
    throw Exception("_keyRestartGame: no game loaded");
}

void Core::_keyMenu()
{
    if (!_menuLoader)
        throw Exception("_keyMenu: no menu loaded");
    resetResource();
    startMenu();
}

void Core::_keyExit()
{
    _currGame.second->stop();
}
