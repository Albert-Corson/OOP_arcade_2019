/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Game
*/

#pragma once

#include "AGame.hpp"
#include <list>
#include <unordered_map>

#define E_MOVE_TIMER 250.0
#define E_SHOOT_TIMER E_MOVE_TIMER * 8.0
#define E_DISABLED_TIMER 2000.0

#define P_MOVE_TIMER 350.0
#define P_SHOOT_TIMER P_MOVE_TIMER * 3.5

#define PL_MOVE_TIMER 125.0
#define EL_MOVE_TIMER 75.0

namespace arcade {
    class Game : public AGame {
        public:
            Game(ICore &core);
            ~Game() override = default;

            void launch() override final;

            static constexpr unsigned boardSizeX = 35;
            static constexpr unsigned boardSizeY = 20;
            static constexpr unsigned powerUpRatio = 15;

            class Asset;
            class Powerup;
            class Player;
            class Enemy;
            class PlayerLaser;
            class EnemyLaser;

            enum orientation_t : int {
                NONE    = 1,
                UP      = NONE << 1,
                DOWN    = UP << 1,
                LEFT    = DOWN << 1,
                RIGHT   = LEFT << 1
            };

            struct ent_type {
                enum _t : int {
                    POWERUP         = orientation_t::RIGHT << 1,
                    WALL            = POWERUP << 1,
                    PLAYER          = WALL << 1,
                    PLAYER_LASER    = PLAYER << 1,
                    ENEMY           = PLAYER_LASER << 1,
                    ENEMY_LASER     = ENEMY << 1
                };
            };

            struct image {
                enum _t : int {
                    POWERUP             = ent_type::POWERUP | NONE,

                    WALL_UP             = ent_type::WALL | UP,
                    WALL_DOWN           = ent_type::WALL | DOWN,
                    WALL_LEFT           = ent_type::WALL | LEFT,
                    WALL_RIGHT          = ent_type::WALL | RIGHT,
                    WALL_UPLEFT         = ent_type::WALL | UP | LEFT,
                    WALL_UPRIGHT        = ent_type::WALL | UP | RIGHT,
                    WALL_DOWNLEFT       = ent_type::WALL | DOWN | LEFT,
                    WALL_DOWNRIGHT      = ent_type::WALL | DOWN | RIGHT,

                    PLAYER_UP           = ent_type::PLAYER | UP,
                    PLAYER_DOWN         = ent_type::PLAYER | DOWN,
                    PLAYER_LEFT         = ent_type::PLAYER | LEFT,
                    PLAYER_RIGHT        = ent_type::PLAYER | RIGHT,

                    PLAYER_LASER_UP     = ent_type::PLAYER_LASER | UP,
                    PLAYER_LASER_DOWN   = ent_type::PLAYER_LASER | DOWN,
                    PLAYER_LASER_LEFT   = ent_type::PLAYER_LASER | LEFT,
                    PLAYER_LASER_RIGHT  = ent_type::PLAYER_LASER | RIGHT,

                    ENEMY_UP            = ent_type::ENEMY | UP,
                    ENEMY_DOWN          = ent_type::ENEMY | DOWN,
                    ENEMY_LEFT          = ent_type::ENEMY | LEFT,
                    ENEMY_RIGHT         = ent_type::ENEMY | RIGHT,

                    ENEMY_LASER_UP      = ent_type::ENEMY_LASER | UP,
                    ENEMY_LASER_DOWN    = ent_type::ENEMY_LASER | DOWN,
                    ENEMY_LASER_LEFT    = ent_type::ENEMY_LASER | LEFT,
                    ENEMY_LASER_RIGHT   = ent_type::ENEMY_LASER | RIGHT,
                };
            };

            struct font {
                enum _t : int {
                    DEFAULT
                };
            };

            struct audio {
                enum _t : int {
                    POWERUP         = ent_type::POWERUP,
                    PLAYER_LASER    = ent_type::PLAYER_LASER,
                    ENEMY_LASER     = ent_type::ENEMY_LASER
                };
            };


            std::unique_ptr<IClock> createClock() const;
            ICore &getCore();
            std::weak_ptr<PlayerLaser> addPlayerLaser(double x, double y, orientation_t dir);
            std::weak_ptr<EnemyLaser> addEnemyLaser(double x, double y, orientation_t dir);


        private:
            typedef void (Game::*keyAction_t)();

            void _loadAssets();
            void _initWalls();
            void _initPowerups();
            void _updateScore();
            void _showPause() const;
            void _showScore(int offsetY = 0) const;
            void _showGame() const;
            void _processKeys();
            void _processAllAssets();
            void _processPlayer();
            void _processPowerups();
            void _processEnemies();

            void _setPlayerDirUp();
            void _setPlayerDirDown();
            void _setPlayerDirLeft();
            void _setPlayerDirRight();
            void _playerShoot();
            void _pause();

            std::unique_ptr<IClock> _gameClock;
            long _playTime;

            int _paused;

            std::unique_ptr<Player> _player;
            std::shared_ptr<PlayerLaser> _playerLaser;

            std::array<std::unique_ptr<Enemy>, 4> _enemies;
            std::list<std::shared_ptr<EnemyLaser>> _enemyLasers;

            std::list<std::unique_ptr<Powerup>> _powerups;
            std::vector<std::unique_ptr<Asset>> _walls;

            std::vector<KeyState> _actionKeys;
            std::unordered_map<Key, keyAction_t> _keyActions;
    };
}

#include "GameAsset.hpp"
