/*
** EPITECH PROJECT, 2022
** B-CPP-500-COT-5-1-rtype-prunella.dousso
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP_
#define IDISPLAY_HPP_

#include <iostream>
#include <memory>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

/**
 * @brief Identifying the moves keys
 *
 */
enum Controller
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

/**
 * @brief Identifying the events types
 *
 */
enum EventType {
    None,
    closed,
    keypressed
};

/**
 * @brief Display library interface class
 *
 */
class IDisplay {
    public:
        virtual ~IDisplay() = default;
        virtual sf::Event create_event(void) = 0;
        //virtual sf::Keyboard::Key GetKeyCode(void) = 0;
        //virtual sf::Sprite &create_sprite(std::string file) = 0;
        virtual void window_close(sf::RenderWindow &window) = 0;
        virtual void displayWindow(sf::RenderWindow &window) = 0;
        virtual EventType check_event_type(sf::Event &events) = 0;
        virtual bool check_opened_window(sf::RenderWindow &window) = 0;
        virtual std::shared_ptr<sf::Sprite> create_sprite(std::shared_ptr<sf::Texture> texture) = 0;
        virtual void window_clear(sf::RenderWindow &window, sf::Color color) = 0;
        virtual void setPosition(std::shared_ptr<sf::Sprite> sprite, sf::Vector2f pos) = 0;
        virtual void setPosition(sf::CircleShape &circleshape, sf::Vector2f pos) = 0;
        virtual void setPosition(sf::RectangleShape &rectangle, sf::Vector2f pos) = 0;
        virtual bool check_event_loop(sf::RenderWindow &window, sf::Event &events) = 0;
        virtual void draw_sprites(sf::RenderWindow &window, std::shared_ptr<sf::Sprite> sprite) = 0;
        virtual void draw_rectangles(sf::RenderWindow &window, sf::RectangleShape &rectangle) = 0;
        virtual void draw_circle_shapes(sf::RenderWindow &window, sf::CircleShape &circleshape) = 0;
        virtual std::shared_ptr<sf::Texture> LoadTexture(std::string file) = 0;
        virtual sf::Time ElapsedTime(std::shared_ptr<sf::Clock> m_clock) = 0;
        virtual sf::Time ClockRestart(std::shared_ptr<sf::Clock> m_clock) = 0;
        //virtual sf::Sprite create_sprite(std::string file, sf::IntRect rect, sf::Vector2f scale) = 0;

    protected:
        std::vector<sf::Texture> textures;
    private:
};

#endif /* !IDISPLAY_HPP_ */
