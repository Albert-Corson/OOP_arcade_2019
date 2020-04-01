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
#include <map>
#include <memory>
#include "ICore.hpp"
#include "Resource.hpp"
#include "games/IGame.hpp"
#include "lib/ILibGraph.hpp"
#include "deps/Exception.hpp"

#define LIBGRAPHS_PATH   "lib/"
#define GAMES_PATH  "games/"
#define MENU_PATH   "menu/"

namespace arcade {
    typedef std::unique_ptr<ILibGraph> (*libGraphLoader_t)();
    typedef std::unique_ptr<IGame> (*gameLoader_t)(ICore &);
    typedef std::unique_ptr<IGame> (*menuLoader_t)(ICore &);

    class Core : public ICore {
        public:
            class Exception;

            struct GameStorage : public LibInfo {
                GameStorage()
                    : LibInfo()
                    , loader(nullptr)
                    , instance(nullptr)
                {}
                GameStorage(const std::string &libPath, const std::string &libName, const gameLoader_t &libLoader)
                    : LibInfo(libPath, libName)
                    , loader(libLoader)
                    , instance(nullptr)
                {}
                GameStorage(const GameStorage &other)
                    : LibInfo(other)
                    , loader(other.loader)
                    , instance(nullptr)
                {}
                GameStorage &operator=(const GameStorage &other)
                {
                    LibInfo::operator=(other);
                    this->loader = other.loader;
                    this->instance = nullptr;
                    return (*this);
                }

                gameLoader_t loader;
                std::unique_ptr<IGame> instance;
            };

            struct LibGraphStorage : public LibInfo {
                LibGraphStorage()
                    : LibInfo()
                    , loader(nullptr)
                    , instance(nullptr)
                {}
                LibGraphStorage(const std::string &libPath, const std::string &libName, const libGraphLoader_t &libLoader)
                    : LibInfo(libPath, libName)
                    , loader(libLoader)
                    , instance(nullptr)
                {}
                LibGraphStorage(const LibGraphStorage &other)
                    : LibInfo(other)
                    , loader(other.loader)
                    , instance(nullptr)
                {}
                LibGraphStorage &operator=(const LibGraphStorage &other)
                {
                    LibInfo::operator=(other);
                    this->loader = other.loader;
                    this->instance = nullptr;
                    return (*this);
                }

                libGraphLoader_t loader;
                std::unique_ptr<ILibGraph> instance;
            };

            Core(const std::string &menuToLoad);
            ~Core();

            void changeLibGraph(const std::string path);
            void changeGame(const std::string path);
            void setLibGraph(const std::string path);
            void setGame(const std::string path);
            void startMenu();
            const std::vector<LibInfo> getLibGraphsList() const;
            const std::vector<LibInfo> getGamesList() const;

            std::unique_ptr<IClock> createClock() override final;
            void loadResourceAudio(int id, std::string filepath) override final;
            void loadResourceFont(int id, std::string filepath) override final;
            void loadResourceImage(int id, std::string filepathGraph, std::string filepathAscii) override final;
            void resetResource() override final;
            void displayImage(int id, int posX, int posY) override final;
            void displayImage(int id, double posX, double posY) override final;
            void displayText(int id, int posX, int posY, std::string const &text) override final;
            void playAudio(int id, bool repeat = false) override final;
            void stopAudio(int id) override final;
            void clear() override final;
            void render() override final;
            void getKeyboardEvents(std::vector<KeyState> &keys) override final;

        private:
            typedef std::string (*libNameGetter_t)();
            typedef void (Core::*keyAction_t)();

            void _loadLibGraph(const std::string name);
            void _loadGame(const std::string name);
            void _loadMenu(const std::string name);
            void _keyPrevGame();
            void _keyNextGame();
            void _keyPrevLib();
            void _keyNextLib();
            void _keyRestartGame();
            void _keyMenu();
            void _keyExit();

            LibGraphStorage _currLib;
            GameStorage _currGame;

            std::vector<LibGraphStorage> _libGraphsInfos;
            std::vector<GameStorage> _gamesInfos;

            gameLoader_t _menuLoader;

            std::unordered_map<int, Resource> _resources;
    };

    class Core::Exception : public arcade::Exception {
        public:
            Exception(const std::string &message)
                : arcade::Exception("Core::Exception " + message)
            {
            };

            const char *what() const throw() override
            {
                return (_msg.c_str());
            };
    };
}
