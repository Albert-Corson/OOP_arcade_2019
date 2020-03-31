/*
** EPITECH PROJECT, 2019
** arcade
** File description:
** icore
*/

#ifndef ICORE_HPP_
#define ICORE_HPP_

#include "IClock.hpp"
#include "deps/keys.hpp"
#include <memory>
#include <vector>

namespace arcade {
    // The arcade core interface
    // It acts as a bridge between the game and the graphical library
    // It handles the resource persistence when switching between the multiple
    // graphical libraries
    class ICore {
        public:
            struct LibInfo {
                LibInfo(const std::string &libPath, const std::string &libName)
                    : path(libPath)
                    , name(libName)
                {}
                const std::string path;
                const std::string name;
            };

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
            virtual void displayImage(int id, int posX, int posY) = 0;
            virtual void displayImage(int id, double posX, double posY) = 0;

            // Draws text at a given position
            virtual void displayText(int id, int posX, int posY, std::string const &text) = 0;

            // Plays an audio resource
            virtual void playAudio(int id, bool repeat = false) = 0;

            // Stops playing an audio resource
            virtual void stopAudio(int id) = 0;

            // Clears the window
            virtual void clear() = 0;

            // Renders the window
            virtual void render() = 0;

            // Returns the latest keyboard events
            virtual void getKeyboardEvents(std::vector<KeyState> &keys) = 0;
    };
}

#endif
