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

Core::Core(const std::string &menuToLoad)
    : _menuLoader(nullptr)
{
    std::string path;
    std::string name;

    _loadMenu(menuToLoad);
    for (auto it : std::filesystem::directory_iterator(LIBGRAPHS_PATH)) {
        if (it.path().extension() == std::filesystem::path(".so"))
            _loadLibGraph(it.path().c_str());
    }
    for (auto it : std::filesystem::directory_iterator(GAMES_PATH)) {
        if (it.path().extension() == std::filesystem::path(".so"))
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
    std::filesystem::path normal_path = std::filesystem::path(path).lexically_normal();
    bool find = false;

    for (const auto &it : _libGraphsInfos) {
        if (it.path == normal_path.c_str()) {
            find = true;
            if (_currGame.instance != nullptr)
                _currGame.instance->stop();
            _currLib = it;
            _currLib.instance = it.loader();
            if (_currGame.instance != nullptr) {
                _currGame.instance = _currGame.loader(*this);
                _currGame.instance->launch();
            }
            break;
        }
    }
    if (!find)
        throw Core::Exception("setLibGraph: No such lib: " + path);
}

void Core::setGame(const std::string path)
{
    std::filesystem::path normal_path = std::filesystem::path(path).lexically_normal();
    bool find = false;

    for (const auto &it : _gamesInfos) {
        if (it.path == normal_path.c_str()) {
            find = true;
            if (_currGame.instance != nullptr)
                _currGame.instance->stop();
            resetResource();
            _currGame = it;
            _currGame.instance = it.loader(*this);
            _currGame.instance->launch();
            break;
        }
    }
    if (!find)
        throw Core::Exception("setGame: No such lib: " + path);
}

void Core::startMenu()
{
    if (!_menuLoader)
        throw Exception("_keyMenu: `_menuLoader` is no set");
    resetResource();
    _currGame.path = "__MENU__";
    _currGame.name = "Menu";
    _currGame.loader = _menuLoader;
    _currGame.instance = _menuLoader(*this);
    _currGame.instance->launch();
}

std::unique_ptr<IClock> Core::createClock()
{
    return (std::make_unique<Clock>());
}

void Core::loadResourceAudio(int id, std::string filepath)
{
    _resources.insert_or_assign(id, Resource(ResourceType::AUDIO, filepath, filepath));
    _currLib.instance->loadResourceAudio(id, filepath);
}

void Core::loadResourceFont(int id, std::string filepath)
{
    _resources.insert_or_assign(id, Resource(ResourceType::FONT, filepath, filepath));
    _currLib.instance->loadResourceFont(id, filepath);
}

void Core::loadResourceImage(int id, std::string filepathGraph, std::string filepathAscii)
{
    _resources.insert_or_assign(id, Resource(ResourceType::IMG, filepathGraph, filepathAscii));
    _currLib.instance->loadResourceImage(id, filepathGraph, filepathAscii);
}

void Core::resetResource()
{
    _currLib.instance->resetResource();
    _resources.clear();
}

void Core::displayImage(int id, int posX, int posY)
{
    _currLib.instance->displayImage(id, posX, posY);
}

void Core::displayImage(int id, double posX, double posY)
{
    _currLib.instance->displayImage(id, posX, posY);
}

void Core::displayText(int id, int posX, int posY, std::string const &text)
{
    _currLib.instance->displayText(id, posX, posY, text);
}

void Core::playAudio(int id, bool repeat)
{
    _currLib.instance->playAudio(id, repeat);
}

void Core::stopAudio(int id)
{
    _currLib.instance->stopAudio(id);
}

void Core::clear()
{
    _currLib.instance->clear();
}

void Core::render()
{
    _currLib.instance->render();
}

void Core::getKeyboardEvents(std::vector<KeyState> &keys)
{
    static std::unordered_map<Key, keyAction_t> actions = {
        { Key::F9, &arcade::Core::_keyPrevGame },
        { Key::F10, &arcade::Core::_keyNextGame },
        { Key::F11, &arcade::Core::_keyPrevLib },
        { Key::F12, &arcade::Core::_keyNextLib },
        { Key::F5, &arcade::Core::_keyRestartGame },
        { Key::F1, &arcade::Core::_keyMenu },
        { Key::F4, &arcade::Core::_keyExit }
    };
    static std::vector<KeyState> coreKeys = {
        KeyState(Key::F9),  // Previous game
        KeyState(Key::F10), // Next game
        KeyState(Key::F11), // Previous library
        KeyState(Key::F12), // Next library
        KeyState(Key::F5),  // Restart game
        KeyState(Key::F1),  // Go back to the menu
        KeyState(Key::F4)   // Exit
    };

    _currLib.instance->getKeyboardEvents(keys, coreKeys);
    for (const auto &it: coreKeys) {
        if (it.is_pressed)
            (this->*actions[it.key])();
    }
}

void Core::_loadLibGraph(const std::string path)
{
    std::string normal_path = std::filesystem::path(path).lexically_normal().c_str();
    libNameGetter_t nameGetter = nullptr;
    libGraphLoader_t loader = nullptr;

    DLLoader lib(normal_path);
    loader = lib.getsym<libGraphLoader_t>("init_graph_lib");
    nameGetter = lib.getsym<libNameGetter_t>("get_lib_name");
    if (!loader || !nameGetter)
        throw Exception(normal_path + " isn't valid");
    _libGraphsInfos.push_back(LibGraphStorage(normal_path, nameGetter(), loader));
}

void Core::_loadGame(const std::string path)
{
    std::string normal_path = std::filesystem::path(path).lexically_normal().c_str();
    libNameGetter_t nameGetter = nullptr;
    gameLoader_t loader = nullptr;

    DLLoader lib(normal_path);
    loader = lib.getsym<gameLoader_t>("init_game_lib");
    nameGetter = lib.getsym<libNameGetter_t>("get_lib_name");
    if (!loader || !nameGetter)
        throw Exception(normal_path + " isn't valid");
    _gamesInfos.push_back(GameStorage(normal_path, nameGetter(), loader));
}

void Core::_loadMenu(const std::string path)
{
    std::string normal_path = std::filesystem::path(path).lexically_normal().c_str();
    DLLoader menu(normal_path);

    _menuLoader = menu.getsym<menuLoader_t>("init_menu_lib");
    if (_menuLoader == NULL)
        throw Exception(normal_path + ": cannot find symbol `init_menu_lib`");
}

void Core::_keyPrevGame()
{
    auto it = _gamesInfos.rbegin();

    for (; it != _gamesInfos.rend(); ++it) {
        if (it->path == _currGame.path)
            break;
    }
    if (it == _gamesInfos.rend())
        it = _gamesInfos.rbegin();
    else
        ++it;
    if (it == _gamesInfos.rend())
        it = _gamesInfos.rbegin();
    this->setGame(it->path);
}

void Core::_keyNextGame()
{
    auto it = _gamesInfos.begin();

    for (; it != _gamesInfos.end(); ++it) {
        if (it->path == _currGame.path)
            break;
    }
    if (it == _gamesInfos.end())
        it = _gamesInfos.begin();
    else
        ++it;
    if (it == _gamesInfos.end())
        it = _gamesInfos.begin();
    this->setGame(it->path);
}

void Core::_keyPrevLib()
{
    auto it = _libGraphsInfos.rbegin();

    for (; it != _libGraphsInfos.rend(); ++it) {
        if (it->path == _currLib.path)
            break;
    }
    if (it == _libGraphsInfos.rend())
        it = _libGraphsInfos.rbegin();
    else
        ++it;
    if (it == _libGraphsInfos.rend())
        it = _libGraphsInfos.rbegin();
    this->setLibGraph(it->path);
}

void Core::_keyNextLib()
{
    auto it = _libGraphsInfos.begin();

    for (; it != _libGraphsInfos.end(); ++it) {
        if (it->path == _currLib.path)
            break;
    }
    if (it == _libGraphsInfos.end())
        it = _libGraphsInfos.begin();
    else
        ++it;
    if (it == _libGraphsInfos.end())
        it = _libGraphsInfos.begin();
    this->setLibGraph(it->path);
}

void Core::_keyRestartGame()
{
    if (_currGame.instance == nullptr)
        throw Exception("_keyRestartGame: no game loaded");
    resetResource();
    _currGame.instance->stop();
    _currGame.instance = _currGame.loader(*this);
    _currGame.instance->launch();
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
    _currGame.instance->stop();
}
