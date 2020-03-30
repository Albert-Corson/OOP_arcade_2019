/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** AGame
*/

#pragma once

#include "IGame.hpp"
#include "deps/Exception.hpp"

namespace arcade {
    class AGame : public IGame {
        public:
            class Exception;
            virtual ~AGame() = default;

            unsigned long getScore() const override
            {
                return (_score);
            };
            void setScore(unsigned long val)
            {
                _score = val;
            };
            unsigned long addScore(unsigned long val)
            {
                _score += val;
                return (_score);
            };

        protected:
            AGame(ICore &core)
                : _core(core)
            {}
            ICore &_core;
            unsigned long _score;
    };

    class AGame::Exception : public arcade::Exception {
        public:
            Exception(const std::string &message)
                : arcade::Exception("AGame::Exception " + message)
            {
            };

            const char *what() const throw() override
            {
                return (_msg.c_str());
            };
    };
}