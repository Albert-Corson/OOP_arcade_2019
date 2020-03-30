/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibGraphSFML
*/

#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "LibGraphSFML.hpp"

using namespace arcade;

std::string get_lib_name()
{
    return ("SFML");
}

std::unique_ptr<ILibGraph> init_graph_lib()
{
    return (std::make_unique<LibGraphSFML>());
}

void LibGraphSFML::getKeyboardEvents(std::vector<KeyState> &keysGame, std::vector<KeyState> &keysCore)
{
    for (auto &it: keysGame) {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(it.key)))
            it.is_pressed = true;
        else
            it.is_pressed = false;
    }
    for (auto &it: keysCore) {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(it.key)))
            it.is_pressed = true;
        else
            it.is_pressed = false;
    }
}

void LibGraphSFML::displayImage(int id, int posX, int posY)
{
    displayImage(id, (double)posX, (double)posY);
}

void LibGraphSFML::displayImage(int id, double posX, double posY)
{
    auto search = _sprites.find(id);
    if (search == _sprites.end())
        throw ALibGraph::Exception("Bad id in displayImage");
    _sprites[id].setPosition(posX, posY);
    _window.draw(_sprites[id]);
}

void LibGraphSFML::displayText(int id, int posX, int posY, std::string const &text)
{
    sf::Text newText;

    auto search = _fonts.find(id);
    if (search == _fonts.end())
        throw ALibGraph::Exception("Bad id in displayText");
    newText.setString(text);
    newText.setFont(_fonts[id]);
    newText.setPosition(posX, posY);
    _window.draw(newText);
}

void LibGraphSFML::playAudio(int id, bool repeat)
{
    auto search = _musics.find(id);
    if (search == _musics.end())
        throw ALibGraph::Exception("Bad id in playAudio");
    if (_musics[id].getLoop() != repeat)
        _musics[id].setLoop(repeat);
    if (_musics[id].getStatus() != sf::SoundSource::Playing)
        _musics[id].play();
}

void LibGraphSFML::stopAudio(int id)
{
    auto search = _musics.find(id);
    if (search == _musics.end())
        throw ALibGraph::Exception("Bad id in stopAudio");
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
    auto search = _musics.find(id);
    if (search != _musics.end())
        throw ALibGraph::Exception("Bad id with file " + filepath);
    if (!_musics[id].openFromFile(filepath))
        throw ALibGraph::Exception("Load " + filepath + ": Failure");
}

void LibGraphSFML::loadResourceFont(int id, std::string const &filepath)
{
    auto search = _fonts.find(id);
    if (search != _fonts.end())
        throw ALibGraph::Exception("Bad id with file " + filepath);
    if (!_fonts[id].loadFromFile(filepath))
        throw ALibGraph::Exception("Load " + filepath + ": Failure");
}

void LibGraphSFML::loadResourceImage(int id, std::string const &filepathGraph, std::string const &filepathAscii)
{
    sf::Texture texture;

    auto search = _sprites.find(id);
    if (search != _sprites.end())
        throw ALibGraph::Exception("Bad id with file " + filepathGraph);
    if (!texture.loadFromFile(filepathGraph))
        throw ALibGraph::Exception("Load " + filepathGraph + ": Failure");
    _sprites[id].setTexture(texture);
}

void LibGraphSFML::resetResource()
{
    _sprites.clear();
    _fonts.clear();
    _musics.clear();
}
