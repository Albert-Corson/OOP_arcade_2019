/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Game
*/

#include "Game.hpp"
#include "assets.hpp"
#include <cmath>

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
    , _paused(true)
    , _player(std::make_unique<Player>(*this, ent_type::PLAYER, boardSizeX / 2, boardSizeY / 2, UP))
    , _playerLaser(nullptr)
    , _enemies {
        std::make_unique<Enemy>(*this, ent_type::ENEMY, 1, 0, DOWN),
        std::make_unique<Enemy>(*this, ent_type::ENEMY, boardSizeX - 1, boardSizeY, UP),
        std::make_unique<Enemy>(*this, ent_type::ENEMY, boardSizeX, 1, LEFT),
        std::make_unique<Enemy>(*this, ent_type::ENEMY, 0, boardSizeY - 1, RIGHT)
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
        if (_paused) {
            _showPause();
        } else {
            _processAssets();
            _showGame();
        }
        _core.render();
    }
    _updateScore();
}

std::unique_ptr<IClock> Game::createClock() const
{
    return (_core.createClock());
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
    _walls.push_back(std::make_unique<Asset>(*this, ent_type::WALL, 0, 0, UP | LEFT));
    _walls.push_back(std::make_unique<Asset>(*this, ent_type::WALL, boardSizeX, 0, UP | RIGHT));
    _walls.push_back(std::make_unique<Asset>(*this, ent_type::WALL, 0, boardSizeY, DOWN | LEFT));
    _walls.push_back(std::make_unique<Asset>(*this, ent_type::WALL, boardSizeX, boardSizeY, DOWN | RIGHT));
    for (unsigned y = 1; y < boardSizeY; ++y) {
        _walls.push_back(std::make_unique<Asset>(*this, ent_type::WALL, 0, y, LEFT));
        _walls.push_back(std::make_unique<Asset>(*this, ent_type::WALL, boardSizeX, y, RIGHT));
    }
    for (unsigned x = 1; x < boardSizeX; ++x) {
        _walls.push_back(std::make_unique<Asset>(*this, ent_type::WALL, x, 0, UP));
        _walls.push_back(std::make_unique<Asset>(*this, ent_type::WALL, x, boardSizeY, DOWN));
    }
}

void Game::_initPowerups()
{
    int tmp = boardSizeX * boardSizeY;
    int nbPowerUps = (tmp * powerUpRatio) / 100;
    std::string check(tmp, ' ');
    int posX;
    int posY;

    srand(time(nullptr));
    if (nbPowerUps < 0 || nbPowerUps > tmp)
        throw Exception("_initPowerups: `powerUpRatio` too high/low");
    for (int i = 0; i < nbPowerUps;) {
        posX = randBetween(0, boardSizeX - 1);
        posY = randBetween(0, boardSizeY - 1);
        tmp = (posY * boardSizeY) + posX;
        if (check[tmp] != '*') {
            ++posX;
            ++posY;
            if (_player->posX == posX && _player->posY == posY)
                continue;
            check[tmp] = '*';
            _powerups.push_back(std::make_unique<Asset>(*this, ent_type::POWERUP, posX, posY));
            ++i;
        }
    }
}

void Game::_updateScore()
{
    setScore((log(pow(_playTime / 1000, 35)) * -1) + 350);
}

void Game::_showPause() const
{
    _core.displayText(font::DEFAULT, 0, 0, "Game paused");
    _showScore(2);
    _core.displayText(font::DEFAULT, 0, 4, "Press [P] to resume");
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

void Game::_processAssets()
{
    for (const auto &it : _walls)
        it->process();
    for (const auto &it : _powerups)
        it->process();
    for (const auto &it : _enemies)
        it->process();
    _player->process();
    if (_playerLaser != nullptr)
        _playerLaser->process();
    for (const auto &it : _enemyLasers) {
        if (it != nullptr)
            it->process();
    }
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
    throw "TO DO";
}

void Game::_pause()
{
    if (!_paused) {
        _playTime += _gameClock->getElapsedTime();
        _updateScore();
    } else {
        _gameClock->reset();
    }
    for (const auto &it : _walls)
        it->pause();
    for (const auto &it : _powerups)
        it->pause();
    for (const auto &it : _enemyLasers) {
        if (it != nullptr)
            it->pause();
    }
    for (const auto &it : _enemies)
        it->pause();
    if (_playerLaser != nullptr)
        _playerLaser->pause();
    _player->pause();
    _paused = !_paused;
}
