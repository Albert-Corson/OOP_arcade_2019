/*
** EPITECH PROJECT, 2020
** OOP_arcade_2020
** File description:
** resource class
*/

#ifndef RESOURCE_HPP_
#define RESOURCE_HPP_

#include <utility>
#include <string>

namespace arcade {
    enum ResourceType {
        AUDIO = 1,
        IMG = 1 << 1
    };

    class Resource {
        public:
            Resource(ResourceType type, std::string &filepathGraph, std::string &filepathAscii);

            bool isType(ResourceType type) const
            {
                return (_type & type);
            };
            bool isTypeAudio() const
            {
                return (_type & ResourceType::AUDIO);
            };
            bool isTypeImg() const
            {
                return (_type & ResourceType::IMG);
            };

            std::string const &getFilepathGraph() const
            {
                return (_filepathGraph);
            };
            std::string const &getFilepathAscii() const
            {
                return (_filepathAscii);
            };

        private:
            ResourceType _type;
            std::string _filepathGraph;
            std::string _filepathAscii;
    };

}

#endif /* !RESOURCE_HPP_ */
