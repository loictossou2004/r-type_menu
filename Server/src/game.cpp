/*
** EPITECH PROJECT, 2022
** B-CPP-500-COT-5-1-rtype-prunella.dousso
** File description:
** game
*/

#include <SFML/Graphics.hpp>

enum Direction {down, left, right, up};

// int main()
// {

//     sf::Vector2i source(1, down);
//     sf::RenderWindow window(sf::VideoMode(1080, 700), "Test");
//     sf::Clock time;
//     sf::Texture image;
//     sf::Sprite sprite;

//     bool jam;
//     image.loadFromFile("foot.png");
//     sprite.setTexture(image);

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//             if(event.type == sf::Event::KeyPressed)
//             {
//                 jam = true;
//             }
//             else
//                 jam = false;
//             if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
//             {
//                 sprite.move(-8, 0);
//                 //source.y = left;
//             } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
//             {
//                 sprite.move(8, 0);
//                 //source.y = right;
//             } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
//             {
//                 sprite.move(0, -8);
//                 //source.y = up;
//             } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
//             {
//                 sprite.move(0, 8);
//                 source.y = down;
//             } if (sprite.getPosition().x <= 0)
//                   sprite.setPosition(sf::Vector2f(0, sprite.getPosition().y));
//             if (sprite.getPosition().y <= 0)
//                 sprite.setPosition(sf::Vector2f(sprite.getPosition().x, 0));
//             if (sprite.getPosition().x >= 800)
//                 sprite.setPosition(sf::Vector2f(800, sprite.getPosition().y));
//             if (sprite.getPosition().y >= 500)
//                 sprite.setPosition(sf::Vector2f(sprite.getPosition().x, 500));
//         }
//         sprite.setScale(sf::Vector2f(0.5, 0.5));
//         sf::Vector2f position(540, 350);
//         if (position.x < 0)
//             position.x = 0;
//         if (position.y < 0)
//             position.y = 0;
//         if (position.x >= 1080)
//             position.x = 1080;
//         if (position.y >= 796)
//             position.y = 796;

//         window.draw(sprite);
//         window.display();
//         window.clear();
//     }

//     return 0;
// }
