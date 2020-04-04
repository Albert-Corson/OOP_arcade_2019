/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#pragma once

#include "ICore.hpp"
#include "Resource.hpp"
#include "deps/Exception.hpp"
#include "games/IGame.hpp"
#include "lib/ILibGraph.hpp"

#include <functional>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#define LIBGRAPHS_PATH  "lib/"
#define GAMES_PATH      "games/"
#define MENU_PATH       "menu/"

namespace arcade {
    typedef std::unique_ptr<ILibGraph> (*libGraphLoader_t)();
    typedef std::unique_ptr<IGame> (*gameLoader_t)(ICore &);
    typedef std::string (*libNameGetter_t)();

    const std::string libGraphLoaderFnName = "init_graph_lib";
    const std::string gameLoaderFnName = "init_game_lib";
    const std::string libNameGetterFnName = "get_lib_name";

    class Core : public ICore {
        public:
            class Exception;

            struct GameStorage;
            struct LibGraphStorage;

            Core(const std::string &menuToLoad, const std::string &libGraph = "");
            ~Core() override;

            void start();

            const std::vector<LibInfo> getLibGraphsList() const;
            const std::vector<LibInfo> getGamesList() const;
            const std::vector<GameScoreboard> getScoreboards() const;
            void setUserName(const std::string &name);
            const std::string &getUserName() const;
            void setLibGraph(const std::string &path);
            void setGame(const std::string &path);

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
            typedef void (Core::*keyAction_t)();
            const std::string __menu__ = "__MENU__";

            void _loadLibGraph(const std::string &name);
            void _loadGame(const std::string &name, bool isMenu = false);
            void _pushRsrcToLibGraph();
            void _setGame(const std::shared_ptr<GameStorage> &game);

            void _keyPrevGame();
            void _keyNextGame();
            void _keyPrevLib();
            void _keyNextLib();
            void _keyRestartGame();
            void _keyMenu();
            void _keyExit();

            std::string _userName;

            std::queue<std::function<void()>> _actionQueue;

            std::weak_ptr<LibGraphStorage> _currLibGraph;
            std::weak_ptr<GameStorage> _currGame;

            std::vector<std::shared_ptr<LibGraphStorage>> _libGraphs;
            std::vector<std::shared_ptr<GameStorage>> _games;

            std::unordered_map<int, Resource> _imageRsrcs;
            std::unordered_map<int, Resource> _audioRsrcs;
            std::unordered_map<int, Resource> _fontRsrcs;
    };
}

class arcade::Core::Exception : public arcade::Exception {
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
