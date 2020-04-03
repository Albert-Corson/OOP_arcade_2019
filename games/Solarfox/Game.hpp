/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Game
*/

#pragma once

#include "AGame.hpp"
#include <unordered_map>

namespace arcade {
    class Game : public AGame {
        public:
            class Asset;

            enum orientation_t : int {
                UP      = 1,
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
                    POWERUP             = ent_type::POWERUP | UP,

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

            Game(ICore &core);
            ~Game() override = default;

            void launch() override final;

        private:
            static constexpr unsigned __boardSizeX = 35;
            static constexpr unsigned __boardSizeY = 20;
            static constexpr unsigned __powerUpRatio = 15;

            typedef void (Game::*keyAction_t)();

            void _loadAssets();
            void _initWalls();
            void _initPowerups();
            void _updateScore();
            void _showPause() const;
            void _showScore(int offsetY = 0) const;
            void _showGame() const;
            void _processKeys();

            void _setPlayerDirUp();
            void _setPlayerDirDown();
            void _setPlayerDirLeft();
            void _setPlayerDirRight();
            void _playerShoot();
            void _pause();

            std::unique_ptr<IClock> _gameClock;
            long _playTime;

            bool _paused;

            unsigned _eatenPowerups;

            std::unique_ptr<Asset> _player;
            std::unique_ptr<Asset> _playerLaser;

            std::array<std::unique_ptr<Asset>, 4> _enemies;
            std::array<std::unique_ptr<Asset>, 4> _enemyLasers;

            std::vector<std::unique_ptr<Asset>> _powerups;
            std::vector<std::unique_ptr<Asset>> _walls;

            std::vector<KeyState> _actionKeys;
            std::unordered_map<Key, keyAction_t> _keyActions;
    };
}

class arcade::Game::Asset {
    public:
        Asset(ent_type::_t type, double x = 0, double y = 0, int orient = UP);

        operator int() const noexcept;

        image::_t getImage() const noexcept;
        void setPosition(double x, double y) noexcept;
        void setPosition(double x, double y, int orient) noexcept;
        void setOrientation(int orient) noexcept;
        void display(ICore &core) const;
        void resetClock(ICore &core);
        long getElapsedTime(bool reset = true);

        ent_type::_t etype;
        double posX;
        double posY;
        int orientation;
        std::unique_ptr<IClock> clock;
};
