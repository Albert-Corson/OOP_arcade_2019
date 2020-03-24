/*
** EPITECH PROJECT, 2019
** arcade
** File description:
** icore
*/

#ifndef ICORE_HPP_
#define ICORE_HPP_

#include <memory>
#include <vector>

#include <IClock.hpp>
#include <keys.hpp>

namespace arcade {
    // The arcade core interface
    // It acts as a bridge between the game and the graphical library
    // It handles the resource persistence when switching between the multiple
    // graphical libraries
    class ICore {
        public:
            virtual ~ICore() = default;

            // Creates a new clock object
            virtual std::unique_ptr<IClock> createClock() = 0;

            // Loads a new sound
            // Throws an exception in case of failure
            virtual void loadResourceAudio(int id, std::string filepath) = 0;

            // Loads a new font
            // Throws an exception in case of failure
            virtual void loadResourceFont(int id, std::string filepath) = 0;

            // Loads a new image
            // Throws an exception in case of failure
            virtual void loadResourceImage(int id, std::string filepathGraph, std::string filepathAscii) = 0;

            // erases all content of resources
            virtual void resetResource() = 0;

            // Draws an image at a given position
            virtual void displayImage(int id, size_t posX, size_t posY) = 0;

            // Returns the latest keyboard events
            virtual void getKeyboardEvents(std::vector<KeyState> &keys) = 0;
    };
}

#endif
