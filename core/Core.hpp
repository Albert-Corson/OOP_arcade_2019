/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "ICore.hpp"
#include "games/IGame.hpp"
#include "lib/ILibGraph.hpp"
#include "deps/Exception.hpp"

#define LIBS_PATH   "lib/"
#define GAMES_PATH  "games/"
#define MENU_PATH   "menu/"

namespace arcade {
    typedef std::unique_ptr<ILibGraph> (*libLoader)();
    typedef std::unique_ptr<IGame> (*gameLoader)();
    typedef std::unique_ptr<IGame> (*menuLoader)();

    class Core : public ICore {
        public:
            class Exception;

            Core();
            ~Core();

            std::unique_ptr<ILibGraph> &loadLib(const std::string name);
            std::unique_ptr<IGame> &loadGame(const std::string name);
            std::unique_ptr<IGame> &loadMenu(const std::string name);
            const std::vector<std::string> getLibsList() const;
            const std::vector<std::string> getGamesList() const;

            std::unique_ptr<IClock> createClock() override final;
            void loadResourceAudio(int id, std::string filepath) override final;
            void loadResourceFont(int id, std::string filepath) override final;
            void loadResourceImage(int id, std::string filepathGraph, std::string filepathAscii) override final;
            void resetResource() override final;
            void displayImage(int id, size_t posX, size_t posY) override final;
            void getKeyboardEvents(std::vector<KeyState> &keys) override final;

        protected:
            std::unordered_map<std::string, std::unique_ptr<ILibGraph>> _libs;
            std::unordered_map<std::string, std::unique_ptr<IGame>> _games;
            std::unique_ptr<IGame> _menu;
    };

    class Core::Exception : public arcade::Exception {
        public:
            Exception(const std::string &message)
                : arcade::Exception(message)
            {
            };

            const char *what() const throw() override
            {
                return (("Core::Exception " + _msg).c_str());
            };
    };
}
