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

std::unique_ptr<ILibGraph> init_graph_lib()
{
    return (std::make_unique<LibGraphSFML>());
}

LibGraphSFML::LibGraphSFML()
{
    std::cout << "New instance of LibGraphSFML" << std::endl;
}

LibGraphSFML::~LibGraphSFML()
{
    std::cout << "Destroyed instance of LigGraphSFML" << std::endl;
}

void LibGraphSFML::getKeyboardEvents(std::vector<KeyState> &keysGame, std::vector<KeyState> &keysCore)
{
    for (size_t i = 0; i < keysGame.size(); i++) {
        keysGame[i].is_pressed = false;
        if (sf::Keyboard::isKeyPressed(convertKey(keysGame[i].key)))
            keysGame[i].is_pressed = true;
    }
    for (size_t i = 0; i < keysCore.size(); i++) {
        keysCore[i].is_pressed = false;
        if (sf::Keyboard::isKeyPressed(convertKey(keysCore[i].key)))
            keysCore[i].is_pressed = true;
    }
}

void LibGraphSFML::displayImage(int id, size_t posX, size_t posY)
{
    displayImage(id, (double)posX, (double)posY);
}

void LibGraphSFML::displayImage(int id, double posX, double posY)
{
    auto search = _sprites.find(id);
    if (search == _sprites.end())
        throw ("Bad id in displayImage");
    _sprites[id].setPosition(posX, posY);
    _window.draw(_sprites[id]);
}

void LibGraphSFML::displayText(int id, size_t posX, size_t posY, std::string const &text)
{
    sf::Text newText;

    auto search = _fonts.find(id);
    if (search == _fonts.end())
        throw ("Bad id in displayText");
    newText.setString(text);
    newText.setFont(_fonts[id]);
    newText.setPosition(posX, posY);
    _window.draw(newText);
}

void LibGraphSFML::playAudio(int id, bool repeat)
{
    auto search = _musics.find(id);
    if (search == _musics.end())
        throw ("Bad id in playAudio");
    if (_musics[id].getLoop() != repeat)
        _musics[id].setLoop(repeat);
    if (_musics[id].getStatus() != sf::SoundSource::Playing)
        _musics[id].play();
}

void LibGraphSFML::stopAudio(int id)
{
    auto search = _musics.find(id);
    if (search == _musics.end())
        throw ("Bad id in stopAudio");
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
        throw ("Bad id with file " + filepath);
    if (!_musics[id].openFromFile(filepath))
        throw ("Load " + filepath + ": Failure");
}

void LibGraphSFML::loadResourceFont(int id, std::string const &filepath)
{
    auto search = _fonts.find(id);
    if (search != _fonts.end())
        throw ("Bad id with file " + filepath);
    if (!_fonts[id].loadFromFile(filepath))
        throw ("Load " + filepath + ": Failure");
}

void LibGraphSFML::loadResourceImage(int id, std::string const &filepathGraph, std::string const &filepathAscii)
{
    sf::Texture texture;

    auto search = _sprites.find(id);
    if (search != _sprites.end())
        throw ("Bad id with file " + filepathGraph);
    if (!texture.loadFromFile(filepathGraph))
        throw ("Load " + filepathGraph + ": Failure");
    _sprites[id].setTexture(texture);
}

void LibGraphSFML::resetResource()
{
    _sprites.clear();
    _fonts.clear();
    _musics.clear();
}

sf::Keyboard::Key LibGraphSFML::convertKey(arcade::Key key)
{
    switch (key)
    {
    case A: return sf::Keyboard::A;
    case B: return sf::Keyboard::B;
    case C: return sf::Keyboard::C;
    case D: return sf::Keyboard::D;
    case E: return sf::Keyboard::E;
    case F: return sf::Keyboard::F;
    case G: return sf::Keyboard::G;
    case H: return sf::Keyboard::H;
    case I: return sf::Keyboard::I;
    case J: return sf::Keyboard::J;
    case K: return sf::Keyboard::K;
    case L: return sf::Keyboard::L;
    case M: return sf::Keyboard::M;
    case N: return sf::Keyboard::N;
    case O: return sf::Keyboard::O;
    case P: return sf::Keyboard::P;
    case Q: return sf::Keyboard::Q;
    case R: return sf::Keyboard::R;
    case S: return sf::Keyboard::S;
    case T: return sf::Keyboard::T;
    case U: return sf::Keyboard::U;
    case V: return sf::Keyboard::V;
    case W: return sf::Keyboard::W;
    case X: return sf::Keyboard::X;
    case Y: return sf::Keyboard::Y;
    case Z: return sf::Keyboard::Z;
    case NUM0: return sf::Keyboard::Num0;
    case NUM1: return sf::Keyboard::Num1;
    case NUM2: return sf::Keyboard::Num2;
    case NUM3: return sf::Keyboard::Num3;
    case NUM4: return sf::Keyboard::Num4;
    case NUM5: return sf::Keyboard::Num5;
    case NUM6: return sf::Keyboard::Num6;
    case NUM7: return sf::Keyboard::Num7;
    case NUM8: return sf::Keyboard::Num8;
    case NUM9: return sf::Keyboard::Num9;
    case ESCAPE: return sf::Keyboard::Escape;
    case LCONTROL: return sf::Keyboard::LControl;
    case LSHIFT: return sf::Keyboard::LShift;
    case LALT: return sf::Keyboard::LAlt;
    case LSYSTEM: return sf::Keyboard::LSystem;
    case RSHIFT: return sf::Keyboard::RShift;
    case RALT: return sf::Keyboard::RAlt;
    case RSYSTEM: return sf::Keyboard::RSystem;
    case MENU: return sf::Keyboard::Menu;
    case LBRACKET: return sf::Keyboard::LBracket;
    case RBRACKET: return sf::Keyboard::RBracket;
    case SEMICOLON: return sf::Keyboard::SemiColon;
    case COMMA: return sf::Keyboard::Comma;
    case PERIOD: return sf::Keyboard::Period;
    case QUOTE: return sf::Keyboard::Quote;
    case SLASH: return sf::Keyboard::Slash;
    case BACKSLASH: return sf::Keyboard::BackSlash;
    case TILDE: return sf::Keyboard::Tilde;
    case EQUAL: return sf::Keyboard::Equal;
    case HYPHEN: return sf::Keyboard::Dash;
    case SPACE: return sf::Keyboard::Space;
    case ENTER: return sf::Keyboard::Return;
    case BACKSPACE: return sf::Keyboard::BackSpace;
    case TAB: return sf::Keyboard::Tab;
    case PAGEUP: return sf::Keyboard::PageUp;
    case PAGEDOWN: return sf::Keyboard::PageDown;
    case END: return sf::Keyboard::End;
    case HOME: return sf::Keyboard::Home;
    case INSERT: return sf::Keyboard::Insert;
    case DELETE: return sf::Keyboard::Delete;
    case ADD: return sf::Keyboard::Add;
    case SUBTRACT: return sf::Keyboard::Subtract;
    case MULTIPLY: return sf::Keyboard::Multiply;
    case DIVIDE: return sf::Keyboard::Divide;
    case LEFT: return sf::Keyboard::Left;
    case RIGHT: return sf::Keyboard::Right;
    case UP: return sf::Keyboard::Up;
    case DOWN: return sf::Keyboard::Down;
    case NUMPAD0: return sf::Keyboard::Numpad0;
    case NUMPAD1: return sf::Keyboard::Numpad1;
    case NUMPAD2: return sf::Keyboard::Numpad2;
    case NUMPAD3: return sf::Keyboard::Numpad3;
    case NUMPAD4: return sf::Keyboard::Numpad4;
    case NUMPAD5: return sf::Keyboard::Numpad5;
    case NUMPAD6: return sf::Keyboard::Numpad6;
    case NUMPAD7: return sf::Keyboard::Numpad7;
    case NUMPAD8: return sf::Keyboard::Numpad8;
    case NUMPAD9: return sf::Keyboard::Numpad9;
    case F1: return sf::Keyboard::F1;
    case F2: return sf::Keyboard::F2;
    case F3: return sf::Keyboard::F3;
    case F4: return sf::Keyboard::F4;
    case F5: return sf::Keyboard::F5;
    case F6: return sf::Keyboard::F6;
    case F7: return sf::Keyboard::F7;
    case F8: return sf::Keyboard::F8;
    case F9: return sf::Keyboard::F9;
    case F10: return sf::Keyboard::F10;
    case F11: return sf::Keyboard::F11;
    case F12: return sf::Keyboard::F12;
    case F13: return sf::Keyboard::F13;
    case F14: return sf::Keyboard::F14;
    case F15: return sf::Keyboard::F15;
    default: return sf::Keyboard::Unknown;
    }
}
