/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibGraphSDL2
*/

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include "ALibGraph.hpp"
#include "deps/Exception.hpp"
#include "SDL2Wrapper.hpp"
#include "init_graph_lib.hpp"

namespace arcade {
    class LibGraphSDL2: public ALibGraph {
        public:
            class Exception;

            LibGraphSDL2();
            ~LibGraphSDL2();

            void getKeyboardEvents(std::vector<KeyState> &keysGame, std::vector<KeyState> &keysCore) override final;
            void displayImage(int id, int posX, int posY) override final;
            void displayImage(int id, double posX, double posY) override final;
            void displayText(int id, int posX, int posY, std::string const &text) override final;
            void playAudio(int id, bool repeat = false) override final;
            void stopAudio(int id) override final;
            void clear() override final;
            void render() override final;
            void loadResourceAudio(int id, std::string const &filepath) override final;
            void loadResourceFont(int id, std::string const &filepath) override final;
            void loadResourceImage(int id, std::string const &filepathGraph, std::string const &filepathAscii) override final;
            void resetResource() override final;

        private:
            SDL::Window _window;
            std::unordered_map<int, SDL::Image> _images;
            std::unordered_map<int, SDL::Font> _fonts;
    };

    class LibGraphSDL2::Exception : public arcade::Exception {
        public:
            Exception(const std::string &message)
                : arcade::Exception("LibGraphSDL2::Exception " + message)
            {
            };

            const char *what() const throw() override
            {
                return (_msg.c_str());
            };
    };
}
