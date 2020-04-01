/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibGraphSFML
*/

#include "LibGraphSFML.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

using namespace arcade;

std::string get_lib_name()
{
    return ("SFML");
}

std::unique_ptr<ILibGraph> init_graph_lib()
{
    return (std::make_unique<LibGraphSFML>());
}

LibGraphSFML::LibGraphSFML()
{
    _window.create(sf::VideoMode::getDesktopMode(), "Arcade", sf::Style::Fullscreen);
}

LibGraphSFML::~LibGraphSFML()
{
    _window.close();
}

void LibGraphSFML::getKeyboardEvents(std::vector<KeyState> &keysGame, std::vector<KeyState> &keysCore)
{
    sf::Event evt;

    for (auto &it : keysGame)
        it.is_pressed = false;
    for (auto &it : keysCore)
        it.is_pressed = false;
    while (_window.pollEvent(evt)) {
        if (evt.type != sf::Event::KeyPressed)
            continue;
        for (auto &it : keysGame) {
            if (evt.key.code == static_cast<sf::Keyboard::Key>(it.key))
                it.is_pressed = true;
        }
        for (auto &it : keysCore) {
            if (evt.key.code == static_cast<sf::Keyboard::Key>(it.key))
                it.is_pressed = true;
        }
    }
}

void LibGraphSFML::displayImage(int id, int posX, int posY)
{
    displayImage(id, (double)posX, (double)posY);
}

void LibGraphSFML::displayImage(int id, double posX, double posY)
{
    auto search = _images.find(id);

    if (search == _images.end())
        throw ALibGraph::Exception("displayImage: invalid image id");
    _images[id].sprite.setPosition(posX * cell_size_x, posY * cell_size_y);
    _window.draw(_images[id].sprite);
}

void LibGraphSFML::displayText(int id, int posX, int posY, std::string const &text)
{
    sf::Text newText;
    auto search = _fonts.find(id);

    if (search == _fonts.end())
        throw ALibGraph::Exception("displayText: invalid fond id");
    newText.setString(text);
    newText.setFont(_fonts[id]);
    newText.setPosition(posX * cell_size_x, posY * cell_size_y);
    newText.setCharacterSize(cell_size_y);
    _window.draw(newText);
}

void LibGraphSFML::playAudio(int id, bool repeat)
{
    auto search = _musics.find(id);

    if (search == _musics.end())
        throw ALibGraph::Exception("playAudio: invalid audio id");
    if (_musics[id].getLoop() != repeat)
        _musics[id].setLoop(repeat);
    if (_musics[id].getStatus() != sf::SoundSource::Playing)
        _musics[id].play();
}

void LibGraphSFML::stopAudio(int id)
{
    auto search = _musics.find(id);

    if (search == _musics.end())
        throw ALibGraph::Exception("stopAudio: invalid audio id");
    if (_musics[id].getStatus() != sf::SoundSource::Stopped)
        _musics[id].stop();
}

void LibGraphSFML::clear()
{
    _window.clear();
}

void LibGraphSFML::render()
{
    _window.display();
}

void LibGraphSFML::loadResourceAudio(int id, std::string const &filepath)
{
    if (!_musics[id].openFromFile(filepath))
        throw ALibGraph::Exception("loadResourceAudio: couldn't load file: " + filepath);
}

void LibGraphSFML::loadResourceFont(int id, std::string const &filepath)
{
    if (!_fonts[id].loadFromFile(filepath))
        throw ALibGraph::Exception("loadResourceFont: couldn't load file: " + filepath);
}

void LibGraphSFML::loadResourceImage(int id, std::string const &filepathGraph, std::string const &filepathAscii)
{
    if (!_images[id].texture.loadFromFile(filepathGraph))
        throw ALibGraph::Exception("loadResourceImage: couldn't load file: " + filepathGraph);
    _images[id].sprite.setTexture(_images[id].texture);
    sf::Vector2u size = _images[id].texture.getSize();
    _images[id].sprite.setScale(cell_size_x / (float)(size.x), cell_size_y / (float)size.y);
}

void LibGraphSFML::resetResource()
{
    _images.clear();
    _fonts.clear();
    _musics.clear();
}
