/*
** EPITECH PROJECT, 2020
** Solarfox
** File description:
** assets
*/

#pragma once

#include "Game.hpp"

namespace arcade {
    static const std::string PATH_TO_ASSETS = "./games/Solarfox/assets/";

    static const std::unordered_map<int, std::pair<std::string, std::string>> IMAGES_TO_LOAD = {
        { Game::image::POWERUP, {
            "img/png/powerup.png",
            "img/txt/powerup.txt"
        }},
        { Game::image::WALL_UP, {
            "img/png/wall.png",
            "img/txt/walls/up_and_down.txt"
        }},
        { Game::image::WALL_DOWN, {
            "img/png/wall.png",
            "img/txt/walls/up_and_down.txt"
        }},
        { Game::image::WALL_LEFT, {
            "img/png/wall.png",
            "img/txt/walls/left.txt"
        }},
        { Game::image::WALL_RIGHT, {
            "img/png/wall.png",
            "img/txt/walls/right.txt"
        }},
        { Game::image::WALL_UPLEFT, {
            "img/png/wall.png",
            "img/txt/walls/upleft.txt"
        }},
        { Game::image::WALL_UPRIGHT, {
            "img/png/wall.png",
            "img/txt/walls/upright.txt"
        }},
        { Game::image::WALL_DOWNLEFT, {
            "img/png/wall.png",
            "img/txt/walls/downleft.txt"
        }},
        { Game::image::WALL_DOWNRIGHT, {
            "img/png/wall.png",
            "img/txt/walls/downright.txt"
        }},
        { Game::image::PLAYER_UP, {
            "img/png/player/up.png",
            "img/txt/player_and_enemy.txt"
        }},
        { Game::image::PLAYER_DOWN, {
            "img/png/player/down.png",
            "img/txt/player_and_enemy.txt"
        }},
        { Game::image::PLAYER_LEFT, {
            "img/png/player/left.png",
            "img/txt/player_and_enemy.txt"
        }},
        { Game::image::PLAYER_RIGHT, {
            "img/png/player/right.png",
            "img/txt/player_and_enemy.txt"
        }},
        { Game::image::PLAYER_LASER_UP, {
            "img/png/player/laser/up.png",
            "img/txt/lasers/vert.txt"
        }},
        { Game::image::PLAYER_LASER_DOWN, {
            "img/png/player/laser/down.png",
            "img/txt/lasers/vert.txt"
        }},
        { Game::image::PLAYER_LASER_LEFT, {
            "img/png/player/laser/left.png",
            "img/txt/lasers/hor.txt"
        }},
        { Game::image::PLAYER_LASER_RIGHT, {
            "img/png/player/laser/right.png",
            "img/txt/lasers/hor.txt"
        }},
        { Game::image::ENEMY_UP, {
            "img/png/enemy/up.png",
            "img/txt/player_and_enemy.txt"
        }},
        { Game::image::ENEMY_DOWN, {
            "img/png/enemy/down.png",
            "img/txt/player_and_enemy.txt"
        }},
        { Game::image::ENEMY_LEFT, {
            "img/png/enemy/left.png",
            "img/txt/player_and_enemy.txt"
        }},
        { Game::image::ENEMY_RIGHT, {
            "img/png/enemy/right.png",
            "img/txt/player_and_enemy.txt"
        }},
        { Game::image::ENEMY_LASER_UP, {
            "img/png/enemy/laser/up.png",
            "img/txt/lasers/vert.txt"
        }},
        { Game::image::ENEMY_LASER_DOWN, {
            "img/png/enemy/laser/down.png",
            "img/txt/lasers/vert.txt"
        }},
        { Game::image::ENEMY_LASER_LEFT, {
            "img/png/enemy/laser/left.png",
            "img/txt/lasers/hor.txt"
        }},
        { Game::image::ENEMY_LASER_RIGHT, {
            "img/png/enemy/laser/right.png",
            "img/txt/lasers/hor.txt"
        }}
    };

    static const std::unordered_map<int, std::string> FONTS_TO_LOAD = {
        { Game::font::DEFAULT , "font.ttf" }
    };

    static const std::unordered_map<int, std::string> AUDIOS_TO_LOAD = {
        { Game::audio::POWERUP, "audio/powerup.ogg" },
        { Game::audio::PLAYER_LASER, "audio/player/laser.ogg" },
        { Game::audio::ENEMY_LASER, "audio/enemy/laser.ogg" }
    };
}
