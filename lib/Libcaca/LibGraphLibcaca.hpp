/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibGraphLibcaca
*/

#pragma once

#include "ALibGraph.hpp"
#include "init_graph_lib.hpp"
#include <caca.h>
#include <unordered_map>

namespace arcade {
    class LibGraphLibcaca : public ALibGraph {
        public:
            LibGraphLibcaca();
            ~LibGraphLibcaca() override;

            void getKeyboardEvents(std::vector<KeyState> &keysGame, std::vector<KeyState> &keysCore) override final;
            void displayImage(int id, int posX, int posY) override final;
            void displayImage(int id, double posX, double posY) override final;
            void displayText(int fontID, int posX, int posY, std::string const &text) override final;
            void playAudio(int id, bool repeat = false) override final {};
            void stopAudio(int id) override final {};
            void clear() override final;
            void render() override final;
            void loadResourceAudio(int id, std::string const &filepath) override final {};
            void loadResourceFont(int id, std::string const &filepath) override final {};
            void loadResourceImage(int id, std::string const &filepathGraph, std::string const &filepathAscii) override final;
            void resetResource() override final;

        private:
            caca_display_t *_display;
            caca_canvas_t *_canvas;
            std::unordered_map<int, std::string> _images;
    };
}
