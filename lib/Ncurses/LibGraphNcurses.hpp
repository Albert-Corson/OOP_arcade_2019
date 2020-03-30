/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibGraphNcurses
*/

#pragma once

#include "ALibGraph.hpp"
#include "init_graph_lib.hpp"
#include <ncurses.h>
#include <unordered_map>

extern "C" {
    namespace arcade {
        class LibGraphNcurses: public ALibGraph {
            public:
                LibGraphNcurses();
                ~LibGraphNcurses();

                void getKeyboardEvents(std::vector<KeyState> &keysGame, std::vector<KeyState> &keysCore) override final;
                void displayImage(int id, size_t posX, size_t posY) override final;
                void displayImage(int id, double posX, double posY) override final;
                void displayText(int fontID, size_t posX, size_t posY, std::string const &text) override final;
                void playAudio(int id, bool repeat = false) override final {};
                void stopAudio(int id) override final {};
                void clear() override final;
                void render() override final;
                void loadResourceAudio(int id, std::string const &filepath) override final {};
                void loadResourceFont(int id, std::string const &filepath) override final {};
                void loadResourceImage(int id, std::string const &filepathGraph, std::string const &filepathAscii) override final;
                void resetResource() override final;

            private:
                struct Image {
                    Image(const std::string &img = "");
                    Image(const Image &other);
                    void operator=(const Image &other);

                    std::string image;
                    int posX;
                    int posY;
                };

                std::unordered_map<int, Image> _images;
        };

    }
}
