/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** main
*/

#include <iostream>
#include "Exception.hpp"
#include "Core.hpp"

void print_usage(const char *bin)
{
    std::cerr << "USAGE" << std::endl;
    std::cerr << "\t" << bin << " path" << std::endl;
    std::cerr << std::endl;
    std::cerr << "DESCRIPTION" << std::endl;
    std::cerr << "\tpath\tpath to graphical library to use by default" << std::endl;
}

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        print_usage(argv[0]);
        return (84);
    }
    arcade::Core core;
    try {
        core.loadLib(argv[1]);
    } catch (const arcade::Exception &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    std::cout << "Libs:" << std::endl;
    for (auto it: core.getLibsList()) {
        try {
            core.loadLib(it);
            std::cout << it << std::endl;
        } catch(const arcade::Exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    std::cout << "Games:" << std::endl;
    for (auto it: core.getGamesList()) {
        try {
            core.loadGame(it);
            std::cout << it << std::endl;
        } catch(const arcade::Exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return (0);
}
