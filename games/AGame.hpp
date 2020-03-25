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

        protected:
            AGame() = default;
    };

    class AGame::Exception : public arcade::Exception {
        public:
            Exception(const std::string &message)
                : arcade::Exception(message)
            {
            };

            const char *what() const throw() override
            {
                return (("AGame::Exception " + _msg).c_str());
            };
    };
}