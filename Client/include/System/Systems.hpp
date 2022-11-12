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
#include "Client/Display/MyLib.hpp"
#include "Client/includes/Client.hpp"

extern struct all_connexions c_connect;

namespace glob
{
    inline std::map<int, sf::Vector2f> ShipPos = {
        {1, (sf::Vector2f){30.0f, 30.0f}},
        {2, (sf::Vector2f){30.0f, 70.0f}},
        {3, (sf::Vector2f){30.0f, 110.0f}},
        {4, (sf::Vector2f){30.0f, 150.0f}},
    };

    inline std::map<int, std::string> ShipFiles = {
        {1, "assets/graphics/players_enemies/player1.png"},
        {2, "assets/graphics/players_enemies/player2.png"},
        {3, "assets/graphics/players_enemies/player3.png"},
        {4, "assets/graphics/players_enemies/player3.png"},
    };
};

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
    };

    struct Controllable
    {
        sf::Keyboard::Key left;
        sf::Keyboard::Key right;
        sf::Keyboard::Key up;
        sf::Keyboard::Key down;
    };

    struct MyId
    {
        size_t myId;
    };

    struct PlayerId
    {
        size_t playerId;
    };

    class DrawSystem
    {
        public:

            /**
             * @brief Construct a new Draw System object
             *
             * @param window
             * @param lib
             */
            DrawSystem(sf::RenderWindow &window, MyLib &lib) : _win(window), _lib(lib){}

            /**
             * @brief Destroy the Draw System object
             *
             */
            ~DrawSystem(){};
            sf::RenderWindow &_win;
            MyLib &_lib;

            /**
             * @brief Create a drawable object
             *
             * @param r
             */
            void drawing_shape(Registry &r) {
                auto &drawable = r.get_components<Drawable>();
                auto &positions = r.get_components<Position>();

                for (size_t i = 0; i < drawable.size() && i < positions.size(); ++ i) {
                    auto &draw = drawable[i];
                    auto &pos = positions[i];
                    if (draw && pos) {
                        auto shape(draw.value().me);
                        float one = positions[i].value()._position.first;
                        float two = positions[i].value()._position.second;
                        _lib.setPosition(shape, (sf::Vector2f){one, two});
                        _lib.draw_sprites(_win, shape);
                    }
                }
            }
    };

    /**
     * @brief System of the other players System
     *
     * @param r
     */
    inline void PlayerPositionSystem(Registry &r) {
        auto &positions = r.get_components<Position>();
        auto const &ids = r.get_components<PlayerId>();

        for ( size_t i = 0; i < positions.size() && i < ids.size(); ++ i) {
            auto const &pos = positions[i];
            auto const &t_ids = ids[i];
            if (pos && t_ids) {
                auto i = t_ids.value().playerId;
                positions[i].value()._position.first = c_connect.OtherPlayers[i].x;
                positions[i].value()._position.second = c_connect.OtherPlayers[i].y;
            }
        }
    }


    class PosiSystem {
        public:
            PosiSystem(NetWorkClient *client) : _client(client){}
            ~PosiSystem() = default;

            /**
             * @brief Update the Position of the Components
             *
             * @param r
             */
            inline void PositionSystem(Registry &r) {
                auto &positions = r.get_components<Position>();
                auto const &velocities = r.get_components<Velocity>();

                for ( size_t i = 0; i < positions.size() && i < velocities.size(); ++ i) {
                    auto const &pos = positions[i];
                    auto const &vel = velocities[i];
                    if (pos && vel) {
                        positions[i].value()._position.first += vel.value()._vx;
                        positions[i].value()._position.second += vel.value()._vy;
                        // std::cout << "x= "<< positions[i].value()._position.first << "; y= " << positions[i].value()._position.second << std::endl;
                        std::string message_Send = "Position:__x=" + to_string(positions[i].value()._position.first) + "__y=" + to_string(positions[i].value()._position.second);
                        // cout << "message_send: " << message_Send;
                        _client->Send_to_Client(message_Send.c_str());
                    }
                }
            }

            NetWorkClient *_client;
    };

    class MoveSystem {
        private:
            double _velo_unit;
        public:

            /**
             * @brief Construct a new Move System object
             *
             * @param events
             */
            MoveSystem(sf::Event &events) : _events(events) {
                _velo_unit = 3;
            };

            /**
             * @brief Destroy the Move System object
             *
             */
            ~MoveSystem(){
                _velo_unit = 3;
            };

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
                                vel.value()._vx = -_velo_unit;
                            if (_events.key.code == con.value().right)
                                vel.value()._vx = _velo_unit;
                            if (_events.key.code == con.value().up)
                                vel.value()._vy = -_velo_unit;
                            if (_events.key.code == con.value().down)
                                vel.value()._vy = _velo_unit;
                        }
                    }
                }
            }
    };
}

#endif /* !STEP3_HPP_ */
