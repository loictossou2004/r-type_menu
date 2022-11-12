/*
** EPITECH PROJECT, 2022
** step0.hpp
** File description:
** entity class
*/

#ifndef MyEntity
#define MyEntity

    #include <algorithm>
    #include <cmath>
    #include <cstring>
    #include <functional>
    #include <fstream>
    #include <iostream>
    #include <list>
    #include <map>
    #include <unordered_map>
    #include <memory>
    #include <sstream>
    #include <csignal>
    #include <string>
    #include <vector>
    #include <chrono>
    #include <thread>

class entity_t
{
    private:
        std::size_t e;
        friend class Registry;
    public:
        /**
         * @brief Construct a new entity t object
         *
         * @param a
         */
        explicit entity_t(std::size_t a) : e(a) {}

        /**
         * @brief Destroy the entity t object
         *
         */
        ~entity_t(){};

        /**
         * @brief Overloading the casting operator
         *
         * @return std::size_t
         */
        operator std::size_t() const {return e;}
};

#endif /* !MyEntity */
