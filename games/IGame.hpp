/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IGame
*/

#pragma once

namespace arcade {
    class IGame {
        public:
            virtual ~IGame() = default;

            // Launches the game loop and transfers the control over to the game
            // Returns once stop() is called
            virtual void launch() = 0;

            // Stops the game loop if it was running
            virtual void stop() = 0;
    };
}
