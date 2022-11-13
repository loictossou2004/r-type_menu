/*
** EPITECH PROJECT, 2022
** B-CPP-500-COT-5-1-rtype-prunella.dousso
** File description:
** encapsulation of the lib
*/

#ifndef MYLIB_HPP_
#define MYLIB_HPP_

#include "IDisplay.hpp"

/**
 * @brief Display library encapsulation class
 *
 */
class MyLib : public IDisplay {
    public:
        /**
         * @brief Construct a new My Lib object
         *
         */
        MyLib(){};

        /**
         * @brief Destroy the My Lib object
         *
         */
        ~MyLib(){};

        /**
         * @brief Create a event object
         *
         * @return sf::Event
         */
        sf::Event create_event(void);
        //sf::Keyboard::Key GetKeyCode(void);

        /**
         * @brief Create a shared pointer on a sprite object
         *
         * @param texture
         * @return std::shared_ptr<sf::Sprite>
         */
        std::shared_ptr<sf::Sprite> create_sprite(std::shared_ptr<sf::Texture> texture);

        std::shared_ptr<sf::Sprite> create_sprite_rect(std::shared_ptr<sf::Texture> texture, sf::IntRect rect);

        std::shared_ptr<sf::Text> create_text(std::shared_ptr<sf::Font> font, std::string);

        /**
         * @brief Close rendered window
         *
         * @param window
         */
        void window_close(sf::RenderWindow &window);

        /**
         * @brief Display the actual rendered window contents
         *
         * @param window
         */
        void displayWindow(sf::RenderWindow &window);

        /**
         * @brief Check and return the right event type
         *
         * @param events
         * @return EventType
         */
        EventType check_event_type(sf::Event &events);

        /**
         * @brief Return the state (open or closed) of the window
         *
         * @param window
         * @return true
         * @return false
         */
        bool check_opened_window(sf::RenderWindow &window);

        /**
         * @brief Clear the window
         *
         * @param window
         * @param color
         */
        void window_clear(sf::RenderWindow &window, sf::Color color);

        /**
         * @brief Set the Position of some sprite object
         *
         * @param sprite
         * @param pos
         */
        void setPosition(std::shared_ptr<sf::Sprite> sprite, sf::Vector2f pos);

        /**
         * @brief Set the Position of CircleShape object
         *
         * @param circleshape
         * @param pos
         */
        void setPosition(sf::CircleShape &circleshape, sf::Vector2f pos);

        /**
         * @brief Set the Position of RectangleShape object
         *
         * @param rectangle
         * @param pos
         */
        void setPosition(sf::RectangleShape &rectangle, sf::Vector2f pos);

        /**
         * @brief Check the actual
         *
         * @param window
         * @param events
         * @return true
         * @return false
         */
        bool check_event_loop(sf::RenderWindow &window, sf::Event &events);

        /**
         * @brief Draw sprite on window
         *
         * @param window
         * @param sprite
         */
        void draw_sprites(sf::RenderWindow &window, std::shared_ptr<sf::Sprite> sprite);

        void draw_text(sf::RenderWindow &window, std::shared_ptr<sf::Text> text);

        /**
         * @brief Draw RectangleShape on window
         *
         * @param window
         * @param rectangle
         */
        void draw_rectangles(sf::RenderWindow &window, sf::RectangleShape &rectangle);

        /**
         * @brief Draw CircleShape on window
         *
         * @param window
         * @param circleshape
         */
        void draw_circle_shapes(sf::RenderWindow &window, sf::CircleShape &circleshape);

        /**
         * @brief Load texture from filename
         *
         * @param file
         * @return std::shared_ptr<sf::Texture>
         */
        std::shared_ptr<sf::Texture> LoadTexture(std::string file);

        std::shared_ptr<sf::Font> LoadFont(std::string file);

        /**
         * @brief Get elapsed time from Clock Object
         *
         * @param m_clock
         * @return sf::Time
         */
        sf::Time ElapsedTime(std::shared_ptr<sf::Clock> m_clock);

        /**
         * @brief Restart Clock Object
         *
         * @param m_clock
         * @return sf::Time
         */
        sf::Time ClockRestart(std::shared_ptr<sf::Clock> m_clock);
    protected:
    private:
};

#endif /* !MYLIB_HPP_ */
