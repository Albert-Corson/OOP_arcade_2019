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
            void pause() override;
    };

    class Game::Enemy : public Game::Asset {
        public:
            Enemy(Game &owner, ent_type::_t type, double x = 0, double y = 0, int orient = NONE);
            ~Enemy() override = default;

            void process() override;
            void pause() override;

        private:
            void _processUp();
            void _processDown();
            void _processLeft();
            void _processRight();
            double _move();
            void _moveHor();
            void _moveVert();

            double _speed;
            bool _active;
            std::pair<std::unique_ptr<IClock>, long> _shootClock;
    };
}
