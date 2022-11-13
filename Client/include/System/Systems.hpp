/*
** EPITECH PROJECT, 2022
** Components types
** File description:
** create different types of components
*/

#ifndef STEP3_HPP_
#define STEP3_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "../Component/Registry.hpp"
#include "../../Display/MyLib.hpp"

namespace MyComponents
{
    struct Position
    {
        Position(float x, float y) {
            _position = std::make_pair(x, y);
        };
        std::pair<float, float> _position;
    };

    struct Velocity
    {
        float _vx;
        float _vy;
        Velocity(float vx, float vy) : _vx(vx), _vy(vy) {}
        ~Velocity(){};
    };

    struct Drawable
    {
        //sf::CircleShape _form;
        std::shared_ptr<sf::Texture> texture;
        std::shared_ptr<sf::Sprite> me;
        int state;
        int life;
        int touchable;
    };

    struct Controllable
    {
        sf::Keyboard::Key left;
        sf::Keyboard::Key right;
        sf::Keyboard::Key up;
        sf::Keyboard::Key down;
        sf::Keyboard::Key space;
    };

    /**
     * @brief Update the Position of the Components
     *
     * @param r
     */
    void PositionSystem(Registry &r) {
        auto &positions = r.get_components<Position>();
        auto const &velocities = r.get_components<Velocity>();

        for ( size_t i = 0; i < positions.size() && i < velocities.size(); ++ i) {
            auto const &pos = positions[i];
            auto const &vel = velocities[i];
            if (pos && vel) {
                positions[i].value()._position.first += vel.value()._vx;
                positions[i].value()._position.second += vel.value()._vy;
            }
        }
    }

    class MoveSystem {
        public:

            /**
             * @brief Construct a new Move System object
             *
             * @param events
             */
            MoveSystem(sf::Event &events) : _events(events) {};

            /**
             * @brief Destroy the Move System object
             *
             */
            ~MoveSystem(){};

            sf::Event &_events;

            /**
             * @brief Update the Position of the Components according to the keys entered
             *
             * @param r
             */
            void VelocitySystem(Registry &r) {
                auto &controllable = r.get_components<Controllable>();
                auto &velocities = r.get_components<Velocity>();

                for (size_t i = 0; i < controllable.size() && i < velocities.size(); ++ i) {
                    auto const &con = controllable[i];
                    auto &vel = velocities[i];
                    if (con && vel) {
                        vel.value()._vx = vel.value()._vy = 0;
                        if (_events.type == sf::Event::KeyPressed) {
                            if (_events.key.code == con.value().left)
                                vel.value()._vx = -0.5;
                            if (_events.key.code == con.value().right)
                                vel.value()._vx = 0.5;
                            if (_events.key.code == con.value().up)
                                vel.value()._vy = -0.5;
                            if (_events.key.code == con.value().down)
                                vel.value()._vy = 0.5;
                        }
                    }
                }
        }
    };
}

#endif /* !STEP3_HPP_ */
