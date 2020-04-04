/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Prompt
*/

#pragma once

#include "class/AScene.hpp"

namespace arcade {
    class Prompt : public AScene {
        public:
            Prompt(GameMenu &game);
            ~Prompt() override = default;

            void draw() final;
            void pollEvents() final;

        private:
            void _confirm();
            void _type(const Key);

            std::string _username{""};
    };
}