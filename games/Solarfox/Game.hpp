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
            typedef void (Game::*keyAction_t)(Key);

            class Asset;

            enum orientation_t {
                UP      = 1,
                DOWN    = UP << 1,
                LEFT    = DOWN << 1,
                RIGHT   = LEFT << 1
            };

            enum class entity_type_t {
                POWERUP         = orientation_t::RIGHT << 1,
                WALL            = POWERUP << 1,
                PLAYER          = WALL << 1,
                PLAYER_LASER    = PLAYER << 1,
                ENEMY           = PLAYER_LASER << 1,
                ENEMY_LASER     = ENEMY << 1
            };

            enum class image_t {
                POWERUP             = (int)entity_type_t::POWERUP,

                WALL_LEFT           = (int)entity_type_t::WALL | LEFT,
                WALL_RIGHT          = (int)entity_type_t::WALL | RIGHT,
                WALL_HOR            = (int)entity_type_t::WALL | LEFT | RIGHT,
                WALL_UPLEFT         = (int)entity_type_t::WALL | UP | LEFT,
                WALL_UPRIGHT        = (int)entity_type_t::WALL | UP | RIGHT,
                WALL_DOWNLEFT       = (int)entity_type_t::WALL | DOWN | LEFT,
                WALL_DOWNRIGHT      = (int)entity_type_t::WALL | DOWN | RIGHT,

                PLAYER_UP           = (int)entity_type_t::PLAYER | UP,
                PLAYER_DOWN         = (int)entity_type_t::PLAYER | DOWN,
                PLAYER_LEFT         = (int)entity_type_t::PLAYER | LEFT,
                PLAYER_RIGHT        = (int)entity_type_t::PLAYER | RIGHT,

                PLAYER_LASER_UP     = (int)entity_type_t::PLAYER_LASER | UP,
                PLAYER_LASER_DOWN   = (int)entity_type_t::PLAYER_LASER | DOWN,
                PLAYER_LASER_LEFT   = (int)entity_type_t::PLAYER_LASER | LEFT,
                PLAYER_LASER_RIGHT  = (int)entity_type_t::PLAYER_LASER | RIGHT,

                ENEMY_UP            = (int)entity_type_t::ENEMY | UP,
                ENEMY_DOWN          = (int)entity_type_t::ENEMY | DOWN,
                ENEMY_LEFT          = (int)entity_type_t::ENEMY | LEFT,
                ENEMY_RIGHT         = (int)entity_type_t::ENEMY | RIGHT,

                ENEMY_LASER_UP      = (int)entity_type_t::ENEMY_LASER | UP,
                ENEMY_LASER_DOWN    = (int)entity_type_t::ENEMY_LASER | DOWN,
                ENEMY_LASER_LEFT    = (int)entity_type_t::ENEMY_LASER | LEFT,
                ENEMY_LASER_RIGHT   = (int)entity_type_t::ENEMY_LASER | RIGHT,
            };

            enum class font_t {
                DEFAULT
            };

            enum class audio_t {
                POWERUP         = (int)entity_type_t::POWERUP,
                PLAYER_LASER    = (int)entity_type_t::PLAYER_LASER,
                ENEMY_LASER     = (int)entity_type_t::ENEMY_LASER
            };

            Game(ICore &core);
            ~Game() override = default;

            void launch() override final;

        private:
            void _loadAssets();

            void _processKeys();
            void _setPlayerDir(Key key);
            void _playerShoot(Key key = Key::UNKNOWN);
            void _pause(Key key = Key::UNKNOWN);

            bool _paused;
            std::vector<KeyState> _actionKeys;
            std::unordered_map<Key, keyAction_t> _keyActions;
    };
}

class arcade::Game::Asset {
    public:
        Asset(entity_type_t type, double x = 0, double y = 0, orientation_t orient = UP);

        image_t getImage() const noexcept;
        void setPosition(double x, double y) noexcept;
        void setPosition(double x, double y, orientation_t orient) noexcept;
        void setOrientation(orientation_t orient) noexcept;

        entity_type_t etype;
        double posX;
        double posY;
        orientation_t orientation;
};
