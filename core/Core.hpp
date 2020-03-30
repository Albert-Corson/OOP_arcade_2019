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
    typedef std::unique_ptr<IGame> (*gameLoader)(ICore &);
    typedef std::unique_ptr<IGame> (*menuLoader)(ICore &);

    class Core : public ICore {
        public:
            class Exception;

            Core();
            ~Core();

            void loadLib(const std::string name);
            void loadGame(const std::string name);
            void loadMenu(const std::string name);
            const std::vector<std::string> getLibsList() const;
            const std::vector<std::string> getGamesList() const;

            std::unique_ptr<IClock> createClock() override final;
            void loadResourceAudio(int id, std::string filepath) override final;
            void loadResourceFont(int id, std::string filepath) override final;
            void loadResourceImage(int id, std::string filepathGraph, std::string filepathAscii) override final;
            void resetResource() override final;
            void displayImage(int id, size_t posX, size_t posY) override final;
            void displayImage(int id, double posX, double posY) override final;
            void displayText(int id, size_t posX, size_t posY, std::string const &text) override final;
            void playAudio(int id, bool repeat = false) override final;
            void stopAudio(int id) override final;
            void clear() override final;
            void render() override final;
            void getKeyboardEvents(std::vector<KeyState> &keys) override final;

        protected:
            std::unique_ptr<ILibGraph> _currLib;
            std::unique_ptr<IGame> _currGame;
            std::unique_ptr<IGame> _currMenu;
            std::unordered_map<std::string, libLoader> _libsLoaders;
            std::unordered_map<std::string, gameLoader> _gamesLoaders;
            gameLoader _menuLoader;
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
