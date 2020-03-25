/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibGraphSFML
*/

#pragma once

#include "ALibGraph.hpp"
#include "init_graph_lib.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

extern "C" {
    namespace arcade {
        class LibGraphSFML: public ALibGraph {
            public:
                LibGraphSFML();
                ~LibGraphSFML();

                void getKeyboardEvents(std::vector<KeyState> &keysGame, std::vector<KeyState> &keysCore) override final;
                void displayImage(int id, size_t posX, size_t posY) override final;
                void displayImage(int id, double posX, double posY) override final;
                void displayText(int id, size_t posX, size_t posY, std::string const &text) override final;
                void playAudio(int id, bool repeat = false) override final;
                void stopAudio(int id) override final;
                void clear() override final;
                void render() override final;
                void loadResourceAudio(int id, std::string const &filepath) override final;
                void loadResourceFont(int id, std::string const &filepath) override final;
                void loadResourceImage(int id, std::string const &filepathGraph, std::string const &filepathAscii) override final;
                void resetResource() override final;

            private:
                sf::Keyboard::Key convertKey(const arcade::Key key);

                sf::RenderWindow _window;
                std::unordered_map<int, sf::Sprite> _sprites;
                std::unordered_map<int, sf::Font> _fonts;
                std::unordered_map<int, sf::Music> _musics;
        };
    }
}