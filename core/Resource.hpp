/*
** EPITECH PROJECT, 2020
** OOP_arcade_2020
** File description:
** resource class
*/

#ifndef RESOURCE_HPP_
#define RESOURCE_HPP_

#include <string>

namespace arcade {
    enum ResourceType {
        AUDIO = 1,
        IMG = 1 << 1
    };

    class Resource {
        public:
        Resource(ResourceType rsrcType, std::string &filepathGraph, std::string &filepathAscii);

        bool isType(ResourceType ofType) const;
        bool isTypeAudio() const;
        bool isTypeImg() const;

        std::string const &getFilepathGraph() const;
        std::string const &getFilepathAscii() const;

        private:
            ResourceType type;
            std::string filepath_graph;
            std::string filepath_ascii;
    };

}

#endif /* !RESOURCE_HPP_ */
