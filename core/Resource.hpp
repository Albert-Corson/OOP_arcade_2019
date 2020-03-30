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
        IMG = 1 << 1,
        FONT
    };

    class Resource {
        public:
            Resource(ResourceType type, const std::string &filepathGraph, const std::string &filepathAscii);

            bool isType(ResourceType type) const;
            bool isTypeAudio() const;
            bool isTypeImg() const;

            std::string const &getFilepathGraph() const;
            std::string const &getFilepathAscii() const;

        private:
            ResourceType _type;
            std::string _filepathGraph;
            std::string _filepathAscii;
    };

}

#endif /* !RESOURCE_HPP_ */
