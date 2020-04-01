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

Core::Core(const std::string &menuToLoad, const std::string &libGraph)
{
    for (const auto &it : std::filesystem::directory_iterator(GAMES_PATH)) {
        if (it.path().extension() == std::filesystem::path(".so"))
            _loadGame(it.path().c_str());
    }
    for (const auto &it : std::filesystem::directory_iterator(LIBGRAPHS_PATH)) {
        if (it.path().extension() == std::filesystem::path(".so"))
            _loadLibGraph(it.path().c_str());
    }
    _loadGame(menuToLoad, true);
    setGame(__menu__);
    if (libGraph != "")
        setLibGraph(libGraph);
}

void Core::start()
{
    while (_actionQueue.size()) {
        _actionQueue.front()();
        _actionQueue.pop();
    }
}

const std::vector<ICore::LibInfo> Core::getLibGraphsList() const
{
    std::vector<LibInfo> keys;

    for (const auto &it : _libGraphs)
        keys.push_back(LibInfo(it->path, it->name));
    return (keys);
}

const std::vector<ICore::LibInfo> Core::getGamesList() const
{
    std::vector<LibInfo> keys;

    for (const auto &it : _games) {
        if (it->path == __menu__)
            continue;
        keys.push_back(LibInfo(it->path, it->name));
    }
    return (keys);
}

void Core::setLibGraph(const std::string &path)
{
    std::string normalPath = std::filesystem::path(path).lexically_normal().c_str();
    auto currLibGraph = _currLibGraph.lock();
    bool find = false;

    if (currLibGraph != nullptr && currLibGraph->path == path)
        return;
    for (const auto &it : _libGraphs) {
        if (it->path == normalPath) {
            find = true;
            if (currLibGraph != nullptr)
                currLibGraph->instance = nullptr;
            _currLibGraph = it;
            it->instance = it->loader();
            _pushRsrcToLibGraph();
            break;
        }
    }
    if (!find)
        throw Core::Exception("setLibGraph: No such lib: " + path);
}

void Core::setGame(const std::string &path)
{
    std::string normalPath = __menu__;
    auto currGame = _currGame.lock();
    bool find = false;

    if (path != __menu__)
        normalPath = std::filesystem::path(path).lexically_normal().c_str();
    for (const auto &it : _games) {
        if (it->path == normalPath) {
            find = true;
            if (currGame != nullptr)
                currGame->instance->stop();
            _actionQueue.push([this, it]() {
                if (_currLibGraph.lock() == nullptr)
                    throw Exception("setGame<lamda>: no graphic library selected");
                resetResource();
                _currGame = it;
                it->instance = it->loader(*this);
                it->instance->launch();
                it->instance = nullptr;
            });
            break;
        }
    }
    if (!find)
        throw Core::Exception("setGame: No such lib: " + path);
}

std::unique_ptr<IClock> Core::createClock()
{
    return (std::make_unique<Clock>());
}

void Core::loadResourceAudio(int id, std::string filepath)
{
    _audioRsrcs.insert_or_assign(id, Resource(filepath, filepath));
    _currLibGraph.lock()->instance->loadResourceAudio(id, filepath);
}

void Core::loadResourceFont(int id, std::string filepath)
{
    _fontRsrcs.insert_or_assign(id, Resource(filepath, filepath));
    _currLibGraph.lock()->instance->loadResourceFont(id, filepath);
}

void Core::loadResourceImage(int id, std::string filepathGraph, std::string filepathAscii)
{
    _imageRsrcs.insert_or_assign(id, Resource(filepathGraph, filepathAscii));
    _currLibGraph.lock()->instance->loadResourceImage(id, filepathGraph, filepathAscii);
}

void Core::resetResource()
{
    auto lib = _currLibGraph.lock();

    if (lib != nullptr)
        _currLibGraph.lock()->instance->resetResource();
    _audioRsrcs.clear();
    _fontRsrcs.clear();
    _imageRsrcs.clear();
}

void Core::displayImage(int id, int posX, int posY)
{
    _currLibGraph.lock()->instance->displayImage(id, posX, posY);
}

void Core::displayImage(int id, double posX, double posY)
{
    _currLibGraph.lock()->instance->displayImage(id, posX, posY);
}

void Core::displayText(int id, int posX, int posY, std::string const &text)
{
    _currLibGraph.lock()->instance->displayText(id, posX, posY, text);
}

void Core::playAudio(int id, bool repeat)
{
    _currLibGraph.lock()->instance->playAudio(id, repeat);
}

void Core::stopAudio(int id)
{
    _currLibGraph.lock()->instance->stopAudio(id);
}

void Core::clear()
{
    _currLibGraph.lock()->instance->clear();
}

void Core::render()
{
    _currLibGraph.lock()->instance->render();
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
        KeyState(Key::F9), // Previous game
        KeyState(Key::F10), // Next game
        KeyState(Key::F11), // Previous library
        KeyState(Key::F12), // Next library
        KeyState(Key::F5), // Restart game
        KeyState(Key::F1), // Go back to the menu
        KeyState(Key::F4) // Exit
    };

    _currLibGraph.lock()->instance->getKeyboardEvents(keys, coreKeys);
    for (const auto &it : coreKeys) {
        if (it.is_pressed)
            (this->*actions[it.key])();
    }
}

void Core::_loadLibGraph(const std::string &path)
{
    std::string normalPath = std::filesystem::path(path).lexically_normal().c_str();
    DLLoader graphLib(normalPath);
    libGraphLoader_t loader = graphLib.getsym<libGraphLoader_t>(arcade::libGraphLoaderFnName);
    libNameGetter_t nameGetter = graphLib.getsym<libNameGetter_t>(arcade::libNameGetterFnName);

    if (!loader || !nameGetter)
        throw Exception("_loadGame: " + normalPath + " isn't a valid game library");
    _libGraphs.push_back(std::make_shared<LibGraphStorage>(normalPath, nameGetter(), loader));
}

void Core::_loadGame(const std::string &path, bool isMenu)
{
    std::string normalPath = std::filesystem::path(path).lexically_normal().c_str();
    DLLoader gameLib(normalPath);
    gameLoader_t loader = gameLib.getsym<gameLoader_t>(arcade::gameLoaderFnName);
    libNameGetter_t nameGetter = gameLib.getsym<libNameGetter_t>(arcade::libNameGetterFnName);
    static bool menuLoaded = false;

    if (!loader || !nameGetter)
        throw Exception("_loadGame: " + normalPath + " isn't a valid game library");
    if (isMenu) {
        normalPath = __menu__;
        if (menuLoaded)
            throw Exception("_loadGame: a menu is already loaded");
        menuLoaded = true;
    }
    _games.push_back(std::make_shared<GameStorage>(normalPath, nameGetter(), loader));
}

void Core::_pushRsrcToLibGraph()
{
    auto lib = _currLibGraph.lock();

    if (lib == nullptr)
        return;
    for (const auto &it : _audioRsrcs)
        lib->instance->loadResourceAudio(it.first, it.second.getFilepathGraph());
    for (const auto &it : _fontRsrcs)
        lib->instance->loadResourceFont(it.first, it.second.getFilepathGraph());
    for (const auto &it : _imageRsrcs)
        lib->instance->loadResourceImage(it.first, it.second.getFilepathGraph(), it.second.getFilepathAscii());
}

void Core::_keyPrevGame()
{
    auto it = _games.rbegin();
    auto end = _games.rend();

    for (; it != end; ++it) {
        if ((*it)->path == _currGame.lock()->path) {
            ++it;
            break;
        }
    }
    if (it == end)
        it = _games.rbegin();
    while (it == end && (*it)->path == __menu__)
        ++it;
    if (it == end)
        throw Exception("_keyPrevGame: No games loaded");
    setGame((*it)->path);
}

void Core::_keyNextGame()
{
    auto it = _games.begin();
    auto end = _games.end();

    for (; it != end; ++it) {
        if ((*it)->path == _currGame.lock()->path) {
            ++it;
            break;
        }
    }
    if (it == end)
        it = _games.begin();
    while (it == end && (*it)->path == __menu__)
        ++it;
    if (it == end)
        throw Exception("_keyNextGame: No games loaded");
    setGame((*it)->path);
}

void Core::_keyPrevLib()
{
    auto it = _libGraphs.rbegin();
    auto end = _libGraphs.rend();

    for (; it != end; ++it) {
        if ((*it)->path == _currLibGraph.lock()->path) {
            ++it;
            break;
        }
    }
    if (it == end)
        it = _libGraphs.rbegin();
    setLibGraph((*it)->path);
}

void Core::_keyNextLib()
{
    auto it = _libGraphs.begin();
    auto end = _libGraphs.end();

    for (; it != end; ++it) {
        if ((*it)->path == _currLibGraph.lock()->path) {
            ++it;
            break;
        }
    }
    if (it == end)
        it = _libGraphs.begin();
    setLibGraph((*it)->path);
}

void Core::_keyRestartGame()
{
    auto game = _currGame.lock();

    if (game == nullptr || game->instance == nullptr)
        throw Exception("_keyRestartGame: no game running");
    setGame(game->path);
}

void Core::_keyMenu()
{
    setGame(__menu__);
}

void Core::_keyExit()
{
    auto game = _currGame.lock();

    if (game != nullptr)
        game->instance->stop();
}
