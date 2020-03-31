/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibGraphSFML
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include "ALibGraph.hpp"

extern "C" {
    namespace arcade {
        class LibGraphSFML: public ALibGraph {
            public:
                LibGraphSFML();
                ~LibGraphSFML();

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
                struct Image {
                    sf::Sprite sprite;
                    sf::Texture texture;
                };

                sf::RenderWindow _window;
                std::unordered_map<int, Image> _images;
                std::unordered_map<int, sf::Font> _fonts;
                std::unordered_map<int, sf::Music> _musics;
        };
    }
}