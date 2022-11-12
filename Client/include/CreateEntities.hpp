/*
** EPITECH PROJECT, 2022
** CReateEntities.hpp
** File description:
** CreateEntities
*/

#ifndef CREATEENTITIES_HPP_
#define CREATEENTITIES_HPP_

#include "Client/include/Component/Registry.hpp"
#include "Client/include/Parallax.hpp"

/**
 * @brief Register Component in the right sparse arrays
 *
 * @param r
 */
void registerComponentType(Registry &r);

/**
 * @brief Register Component in the right sparse arrays
 *
 * @param r
 */
void create_component_me(Registry &r, MyLib &lib, std::string file, sf::Vector2f pos);

/**
 * @brief Create a component parallax object
 *
 * @param r
 * @param lib
 * @param file
 * @param s
 */
void create_component_parallax(Registry &r, MyLib &lib, std::string file, float s);

/**
 * @brief Create a component enemy object
 *
 * @param r
 * @param lib
 * @param file
 */
void create_component_enemy(Registry &r, MyLib &lib, std::string file);

/**
 * @brief Initialize the parallax
 *
 * @param r
 * @param lib
 */
void initialize_parallax(Registry &r, MyLib &lib);

/**
 * @brief Create a component corresponding to another player
 *
 * @param r
 * @param lib
 * @param file
 * @param pos
 * @param id
 */
void create_component_players(Registry &r, MyLib &lib, std::string file, sf::Vector2f pos, size_t id);

#endif /* !CREATEENTITIES_HPP_ */
