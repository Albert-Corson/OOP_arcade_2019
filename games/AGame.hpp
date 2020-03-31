/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** AGame
*/

#pragma once

#include "IGame.hpp"
#include "deps/Exception.hpp"
#include "init_game_lib.hpp"
#include "deps/get_lib_name.hpp"

namespace arcade {
    class AGame : public IGame {
        public:
            class Exception;
            virtual ~AGame() = default;

            void stop() override
            {
                _running = false;
            };
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
                , _score(0)
                , _running(false)
            {}
            ICore &_core;
            unsigned long _score;
            bool _running;
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