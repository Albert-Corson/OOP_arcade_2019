/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibGraphSFML
*/

#pragma once

#include "ALibGraph.hpp"
#include <SFML/Graphics.hpp>

extern "C" {
    class LibGraphSFML: public ALibGraph {
        public:
            LibGraphSFML();
            ~LibGraphSFML();

            virtual void createWindow(std::size_t width, std::size_t height);
            virtual void render() const;

        protected:
            std::unique_ptr<sf::RenderWindow> _window;
    };
}