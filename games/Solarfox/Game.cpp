/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Game
*/

#include "Game.hpp"
#include "assets.hpp"

using namespace arcade;

static int randBetween(int low, int high)
{
    float random = static_cast<float>(rand() + low);

    random /= static_cast<float>(RAND_MAX / (high - low));
    return (random);
}

Game::Game(ICore &core)
    : AGame(core)
    , _gameClock(core.createClock())
    , _playTime(0)
    , _paused(false)
    , _eatenPowerups(0)
    , _player(std::make_unique<Asset>(ent_type::PLAYER, __boardSizeX / 2, __boardSizeY / 2))
    , _playerLaser(nullptr)
    , _enemies {
        std::make_unique<Asset>(ent_type::ENEMY, 1, 0, DOWN),
        std::make_unique<Asset>(ent_type::ENEMY, __boardSizeX - 1, __boardSizeY, UP),
        std::make_unique<Asset>(ent_type::ENEMY, __boardSizeX, 1, LEFT),
        std::make_unique<Asset>(ent_type::ENEMY, 0, __boardSizeY - 1, RIGHT)
    }
    , _enemyLasers { nullptr }
{
    _initPowerups();
    _initWalls();
    _keyActions = {
        { Key::UP, &Game::_setPlayerDirUp },
        { Key::DOWN, &Game::_setPlayerDirDown },
        { Key::LEFT, &Game::_setPlayerDirLeft },
        { Key::RIGHT, &Game::_setPlayerDirRight },
        { Key::SPACE, &Game::_playerShoot },
        { Key::P, &Game::_pause }
    };
    for (const auto &it : _keyActions)
        _actionKeys.push_back(KeyState(it.first));
    _loadAssets();
}

void Game::launch()
{
    _running = true;
    _gameClock->reset();

    while (_running) {
        _core.getKeyboardEvents(_actionKeys);
        _processKeys();
        _core.clear();
        if (_paused)
            _showPause();
        else
            _showGame();
        _core.render();
    }
    _updateScore();
}

void Game::_loadAssets()
{
    for (const auto &it : IMAGES_TO_LOAD)
        _core.loadResourceImage(it.first, PATH_TO_ASSETS + it.second.first, PATH_TO_ASSETS + it.second.second);
    for (const auto &it : FONTS_TO_LOAD)
        _core.loadResourceFont(it.first, PATH_TO_ASSETS + it.second);
    for (const auto &it : AUDIOS_TO_LOAD)
        _core.loadResourceAudio(it.first, PATH_TO_ASSETS + it.second);
}

void Game::_initWalls()
{
    _walls.push_back(std::make_unique<Asset>(ent_type::WALL, 0, 0, UP | LEFT));
    _walls.push_back(std::make_unique<Asset>(ent_type::WALL, __boardSizeX, 0, UP | RIGHT));
    _walls.push_back(std::make_unique<Asset>(ent_type::WALL, 0, __boardSizeY, DOWN | LEFT));
    _walls.push_back(std::make_unique<Asset>(ent_type::WALL, __boardSizeX, __boardSizeY, DOWN | RIGHT));
    for (unsigned y = 1; y < __boardSizeY; ++y) {
        _walls.push_back(std::make_unique<Asset>(ent_type::WALL, 0, y, LEFT));
        _walls.push_back(std::make_unique<Asset>(ent_type::WALL, __boardSizeX, y, RIGHT));
    }
    for (unsigned x = 1; x < __boardSizeX; ++x) {
        _walls.push_back(std::make_unique<Asset>(ent_type::WALL, x, 0, UP));
        _walls.push_back(std::make_unique<Asset>(ent_type::WALL, x, __boardSizeY, DOWN));
    }
}

void Game::_initPowerups()
{
    int tmp = __boardSizeX * __boardSizeY;
    int nbPowerUps = (tmp * __powerUpRatio) / 100;
    std::string check(tmp, ' ');
    int posX;
    int posY;

    srand(time(nullptr));
    if (nbPowerUps < 0 || nbPowerUps > tmp)
        throw Exception("_initPowerups: `__powerUpRatio` too high/low");
    for (int i = 0; i < nbPowerUps;) {
        posX = randBetween(0, __boardSizeX - 1);
        posY = randBetween(0, __boardSizeY - 1);
        tmp = (posY * __boardSizeY) + posX;
        if (check[tmp] != '*') {
            ++posX;
            ++posY;
            if (_player->posX == posX && _player->posY == posY)
                continue;
            check[tmp] = '*';
            _powerups.push_back(std::make_unique<Asset>(ent_type::POWERUP, posX, posY));
            ++i;
        }
    }
}

void Game::_updateScore()
{
    // throw "TO DO";
}

void Game::_showPause() const
{
    _core.displayText(font::DEFAULT, 0, 0, "Game paused");
    _showScore(1);
}

void Game::_showScore(int offsetY) const
{
    _core.displayText(font::DEFAULT, 0, offsetY, "Score: " + std::to_string(_score));
}

void Game::_showGame() const
{
    for (const auto &it : _walls)
        it->display(_core);
    for (const auto &it : _powerups)
        it->display(_core);
    for (const auto &it : _enemyLasers) {
        if (it != nullptr)
            it->display(_core);
    }
    for (const auto &it : _enemies)
        it->display(_core);
    if (_playerLaser != nullptr)
        _playerLaser->display(_core);
    _player->display(_core);
}

void Game::_processKeys()
{
    for (const auto &it : _actionKeys) {
        if (it.is_pressed)
            (this->*_keyActions[it.key])();
    }
}

void Game::_setPlayerDirUp()
{
    if (_player->orientation != DOWN)
        _player->setOrientation(UP);
}

void Game::_setPlayerDirDown()
{
    if (_player->orientation != UP)
        _player->setOrientation(DOWN);
}

void Game::_setPlayerDirLeft()
{
    if (_player->orientation != RIGHT)
        _player->setOrientation(LEFT);
}

void Game::_setPlayerDirRight()
{
    if (_player->orientation != LEFT)
        _player->setOrientation(RIGHT);
}

void Game::_playerShoot()
{
    // throw "TO DO";
}

void Game::_pause()
{
    if (!_paused) {
        _playTime += _gameClock->getElapsedTime();
        _updateScore();
    } else {
        for (const auto &it : _walls)
            it->resetClock(_core);
        for (const auto &it : _powerups)
            it->resetClock(_core);
        for (const auto &it : _enemyLasers) {
            if (it != nullptr)
                it->resetClock(_core);
        }
        for (const auto &it : _enemies)
            it->resetClock(_core);
        if (_playerLaser != nullptr)
            _playerLaser->resetClock(_core);
        _player->resetClock(_core);
        _gameClock->reset();
    }
    _paused = !_paused;
}
