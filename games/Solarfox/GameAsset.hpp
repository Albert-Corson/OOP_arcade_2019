/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** GameAsset
*/

#pragma once

#include "Game.hpp"

namespace arcade {
    class Game::Asset {
        public:
            Asset(Game &owner, ent_type::_t type, double x = 0, double y = 0, int orient = NONE);
            virtual ~Asset() = default;

            operator int() const noexcept;

            image::_t getImage() const noexcept;
            void setPosition(double x, double y) noexcept;
            void setPosition(double x, double y, int orient) noexcept;
            void setOrientation(int orient) noexcept;
            void display(ICore &core) const;
            virtual void process();
            virtual void pause();
            bool collidesWith(Asset &other);

            ent_type::_t etype;
            double posX;
            double posY;
            int orientation;

        protected:
            bool _paused;
            Game &_owner;
            std::pair<std::unique_ptr<IClock>, long> _mainClock;
    };

    class Game::Player : public Game::Asset {
        public:
            Player(Game &owner, ent_type::_t type, double x = 0, double y = 0, int orient = NONE);
            ~Player() override = default;

            void process() override;
            void shoot();
            void switchSpeed();

        private:
            bool _isDead();
            void _move();
            void _moveUp(double step, int lastDir);
            void _moveDown(double step, int lastDir);
            void _moveLeft(double step, int lastDir);
            void _moveRight(double step, int lastDir);

            bool _goFast;
            std::weak_ptr<Game::PlayerLaser> _laser;
    };

    class Game::Enemy : public Game::Asset {
        public:
            Enemy(Game &owner, ent_type::_t type, double x = 0, double y = 0, int orient = NONE);
            ~Enemy() override = default;

            void process() override;
            void pause() override;
            void disable();

        private:
            void _processUp();
            void _processDown();
            void _processLeft();
            void _processRight();
            double _move();
            void _moveHor();
            void _moveVert();
            bool _canShoot();
            void _shoot(double x, double y, orientation_t dir);

            double _speed;
            bool _active;
            std::pair<std::unique_ptr<IClock>, long> _shootClock;
            std::weak_ptr<Game::EnemyLaser> _laser;
    };

    class Game::Powerup : public Game::Asset {
        public:
            Powerup(Game &owner, ent_type::_t type, double x = 0, double y = 0, int orient = NONE);
            ~Powerup() override = default;

            void playDeathSound();
    };

    class Game::PlayerLaser : public Game::Asset {
        public:
            PlayerLaser(Game &owner, ent_type::_t type, double x = 0, double y = 0, int orient = NONE);
            ~PlayerLaser() override = default;

            void process() override;
            bool isDead();

        private:
            void _move();
            void _moveUp(double step);
            void _moveDown(double step);
            void _moveLeft(double step);
            void _moveRight(double step);
    };

    class Game::EnemyLaser : public Game::Asset {
        public:
            EnemyLaser(Game &owner, ent_type::_t type, double x = 0, double y = 0, int orient = NONE);
            ~EnemyLaser() override = default;

            void process() override;
            bool isDead();

        private:
            void _move();
            void _moveUp(double step);
            void _moveDown(double step);
            void _moveLeft(double step);
            void _moveRight(double step);
    };
}
