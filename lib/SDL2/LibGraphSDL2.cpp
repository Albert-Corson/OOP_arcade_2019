/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibGraphSDL2
*/

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include "LibGraphSDL2.hpp"
#include "SDL2Keys.hpp"

using namespace arcade;

LibGraphSDL2::LibGraphSDL2()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    TTF_Init();
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    _window.create(
        "Arcade",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_SHOWN
    );
}

LibGraphSDL2::~LibGraphSDL2()
{
    this->resetResource();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void LibGraphSDL2::getKeyboardEvents(std::vector<KeyState> &keysGame, std::vector<KeyState> &keysCore)
{
    SDL_Event evt;

    for (auto &it : keysGame)
        it.is_pressed = false;
    for (auto &it : keysCore)
        it.is_pressed = false;
    while (SDL_PollEvent(&evt)) {
        if (evt.type != SDL_EventType::SDL_KEYDOWN)
            continue;
        if (SDL2_KEYMAP.find(evt.key.keysym.sym) == SDL2_KEYMAP.end())
            continue;
        for (auto &it: keysCore) {
            if (it.key == SDL2_KEYMAP.at(evt.key.keysym.sym))
                it.is_pressed = true;
        }
        for (auto &it: keysGame) {
            if (it.key == SDL2_KEYMAP.at(evt.key.keysym.sym))
                it.is_pressed = true;
        }
    }
}

void LibGraphSDL2::displayImage(int id, int posX, int posY)
{
    displayImage(id, static_cast<double>(posX), static_cast<double>(posY));
}

void LibGraphSDL2::displayImage(int id, double posX, double posY)
{
    try {
        SDL::Image &img = _images.at(id);
        img.setPosition(posX * cell_size_x, posY * cell_size_y);
        img.display();
    } catch (...) {
        throw Exception("displayImage: incorrect id: " + std::to_string(id));
    }
}

void LibGraphSDL2::displayText(int id, int posX, int posY, std::string const &text)
{
    auto search = _fonts.find(id);

    if (search == _fonts.end())
        throw Exception("displayText: invalid font id: " + std::to_string(id));
    SDL::Text textImg(_window.getRenderer(), *_fonts[id], text);
    textImg.setPosition(posX * cell_size_x, posY * cell_size_y);
    textImg.display();
}

void LibGraphSDL2::clear()
{
    _window.clear();
}

void LibGraphSDL2::render()
{
    _window.refresh();
}

void LibGraphSDL2::loadResourceAudio(int id, std::string const &filepath)
{
}

void LibGraphSDL2::loadResourceFont(int id, std::string const &filepath)
{
    if (!_fonts[id].loadFromFile(filepath, cell_size_y))
        throw Exception("loadRessourceFont: couldn't load file: " + filepath);
}

void LibGraphSDL2::loadResourceImage(int id, std::string const &filepathGraph, std::string const &filepathAscii)
{
    if (!_images[id].loadFromFile(_window.getRenderer(), filepathGraph))
        throw Exception("loadRessourceImage: couldn't load file: " + filepathGraph);
}

void LibGraphSDL2::playAudio(int id, bool repeat)
{
}

void LibGraphSDL2::stopAudio(int id)
{
}

void LibGraphSDL2::resetResource()
{
    _fonts.clear();
    _images.clear();
}
