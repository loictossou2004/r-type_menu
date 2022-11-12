/*
** EPITECH PROJECT, 2022
** B-CPP-500-COT-5-1-rtype-prunella.dousso
** File description:
** Encapsulation of the functions of the lib
*/

#include <iostream>
#include "../Display/MyLib.hpp"

sf::Event MyLib::create_event(void)
{
    sf::Event events;
    return events;
}

bool MyLib::check_opened_window(sf::RenderWindow &window)
{
    if (window.isOpen())
        return true;
    return false;
}

bool MyLib::check_event_loop(sf::RenderWindow &window, sf::Event &events)
{
    if (window.pollEvent(events))
        return true;
    return false;
}

EventType MyLib::check_event_type(sf::Event &events)
{
    if (events.type == sf::Event::Closed)
        return (EventType::closed);
    if (events.type == sf::Event::KeyPressed)
        return (EventType::keypressed);
    return (EventType::None);
}

void MyLib::window_close(sf::RenderWindow &window)
{
    window.close();
}

void MyLib::window_clear(sf::RenderWindow &window, sf::Color color)
{
    window.clear(color);
}

void MyLib::draw_sprites(sf::RenderWindow &window, std::shared_ptr<sf::Sprite> sprite)
{
    window.draw(*sprite);
}

void MyLib::draw_circle_shapes(sf::RenderWindow &window, sf::CircleShape &circleshape)
{
    window.draw(circleshape);
}

void MyLib::draw_rectangles(sf::RenderWindow &window, sf::RectangleShape &rectangle)
{
    window.draw(rectangle);
}

std::shared_ptr<sf::Texture> MyLib::LoadTexture(std::string file)
{
    sf::Texture texture;
    texture.loadFromFile(file);
    return (std::make_shared<sf::Texture>(texture));
}

std::shared_ptr<sf::Sprite> MyLib::create_sprite(std::shared_ptr<sf::Texture> texture)
{
    sf::Sprite sprite;
    sprite.setTexture(*texture);
    return (std::make_shared<sf::Sprite>(sprite));
}

/*sf::Sprite MyLib::create_sprite(std::string file, sf::IntRect rect, sf::Vector2f scale)
{
    sf::Texture texture;
    texture.loadFromFile(file);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.scale(scale);
    return (sprite);
}*/

void MyLib::setPosition(std::shared_ptr<sf::Sprite> sprite, sf::Vector2f pos)
{
    (*sprite).setPosition(pos);
}

void MyLib::setPosition(sf::CircleShape &circleshape, sf::Vector2f pos)
{
    circleshape.setPosition(pos);
}

void MyLib::setPosition(sf::RectangleShape &rectangle, sf::Vector2f pos)
{
    rectangle.setPosition(pos);
}

void MyLib::displayWindow(sf::RenderWindow &window)
{
    window.display();
}

sf::Time MyLib::ElapsedTime(std::shared_ptr<sf::Clock> m_clock)
{
    sf::Time time = (*m_clock).getElapsedTime();
    return time;
}

sf::Time MyLib::ClockRestart(std::shared_ptr<sf::Clock> m_clock)
{
    sf::Time time = (*m_clock).restart();
    return time;
}
