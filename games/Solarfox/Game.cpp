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
    , _paused(0)
    , _player(std::make_unique<Player>(*this, ent_type::PLAYER, boardSizeX / 2, boardSizeY / 2, UP))
    , _playerLaser(nullptr)
    , _enemies {
        std::make_unique<Enemy>(*this, ent_type::ENEMY, 1, 0, DOWN),
        std::make_unique<Enemy>(*this, ent_type::ENEMY, boardSizeX - 1, boardSizeY, UP),
        std::make_unique<Enemy>(*this, ent_type::ENEMY, boardSizeX, 1, LEFT),
        std::make_unique<Enemy>(*this, ent_type::ENEMY, 0, boardSizeY - 1, RIGHT)
    }
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
    _gameClock->reset();
    _pause();
}

void Game::launch()
{
    _running = true;
    _gameClock->reset();

    while (_running) {
        _core.getKeyboardEvents(_actionKeys);
        _processKeys();
        _core.clear();
        if (!_paused) {
            _processAllAssets();
            _showGame();
        } else
            _showPause();
        _core.render();
    }
    _paused = -1;
    _updateScore();
    _running = true;
    _gameClock->reset();
    while (_running && _gameClock->getElapsedTime() < 2500) {
        _core.getKeyboardEvents(_actionKeys);
        _processKeys();
        _core.clear();
        _showScore();
        _core.render();
    }
}

std::unique_ptr<IClock> Game::createClock() const
{
    return (_core.createClock());
}

ICore &Game::getCore()
{
    return (_core);
}

std::weak_ptr<Game::PlayerLaser> Game::addPlayerLaser(double x, double y, orientation_t dir)
{
    _playerLaser = std::make_shared<PlayerLaser>(*this, ent_type::PLAYER_LASER, x, y, dir);
    return (_playerLaser);
}

std::weak_ptr<Game::EnemyLaser> Game::addEnemyLaser(double x, double y, orientation_t dir)
{
    _enemyLasers.push_back(std::make_shared<EnemyLaser>(*this, ent_type::ENEMY_LASER, x, y, dir));
    return (_enemyLasers.back());
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
            _powerups.push_back(std::make_unique<Powerup>(*this, ent_type::POWERUP, posX, posY));
            ++i;
        }
    }
}

void Game::_updateScore()
{
    setScore(((log(pow((_gameClock->getElapsedTime() - _playTime + 10) / 1000, 35)) * -1) + 15000) / _powerups.size());
}

void Game::_showPause() const
{
    static const std::string pauseStr = "Game paused";
    static const std::string helpStr = "Press [P] to resume";
    static const int centerX = (boardSizeX) / 2;
    static const int centerY = (boardSizeY) / 2;

    _core.displayText(font::DEFAULT, centerX - pauseStr.size() / 2, centerY - 2, pauseStr);
    _showScore();
    _core.displayText(font::DEFAULT, centerX - helpStr.size() / 2, centerY + 2, helpStr);
}

void Game::_showScore(int offsetY) const
{
    const std::string scoreStr = "Score: " + std::to_string(_score);

    _core.displayText(font::DEFAULT, (boardSizeX - scoreStr.size()) / 2, (boardSizeY / 2) + offsetY, scoreStr);
}

void Game::_showGame() const
{
    for (const auto &it : _walls)
        it->display(_core);
    for (const auto &it : _powerups)
        it->display(_core);
    for (const auto &it : _enemyLasers)
        it->display(_core);
    for (const auto &it : _enemies)
        it->display(_core);
    if (_playerLaser != nullptr)
        _playerLaser->display(_core);
    _player->display(_core);
}

void Game::_processAllAssets()
{
    if (!_powerups.size()) {
        stop();
        return;
    }
    _processPlayer();
    _processEnemies();
    _processPowerups();
}

void Game::_processPlayer()
{
    _player->process();
}

void Game::_processPowerups()
{
    auto end = _powerups.end();

    for (auto it = _powerups.begin(); it != end;) {
        if ((*it)->collidesWith(*_player))
            it = _powerups.erase(it);
        else if (_playerLaser != nullptr && (*it)->collidesWith(*_playerLaser)) {
            it = _powerups.erase(it);
            _playerLaser = nullptr;
        } else
            ++it;
    }
}

void Game::_processEnemies()
{
    auto end = _enemyLasers.end();

    if (_playerLaser != nullptr)
        _playerLaser->process();
    for (const auto &it : _enemies) {
        if (_playerLaser != nullptr && it->collidesWith(*_playerLaser))
            it->disable();
        it->process();
    }
    if (_playerLaser != nullptr && _playerLaser->isDead())
        _playerLaser = nullptr;
    for (auto it = _enemyLasers.begin(); it != end;) {
        (*it)->process();
        if ((*it)->collidesWith(*_player)) {
            stop();
            return;
        } else if (_playerLaser != nullptr && (*it)->collidesWith(*_playerLaser)) {
            _playerLaser = nullptr;
            it = _enemyLasers.erase(it);
        } else if ((*it)->isDead())
            it = _enemyLasers.erase(it);
        else
            ++it;
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
    _player->shoot();
}

void Game::_pause()
{
    if (_paused != 0 && _paused != 1)
        return;
    if (!_paused) {
        _playTime += _gameClock->getElapsedTime();
        _updateScore();
    } else
        _gameClock->reset();
    for (const auto &it : _walls)
        it->pause();
    for (const auto &it : _powerups)
        it->pause();
    for (const auto &it : _enemyLasers) {
        it->pause();
    }
    for (const auto &it : _enemies)
        it->pause();
    if (_playerLaser != nullptr)
        _playerLaser->pause();
    _player->pause();
    _paused = !_paused;
}
