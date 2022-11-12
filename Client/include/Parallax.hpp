/*
** EPITECH PROJECT, 2022
** B-CPP-500-COT-5-1-rtype-prunella.dousso
** File description:
** Parallax
*/

#ifndef PARALLAX_HPP_
#define PARALLAX_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Component/Registry.hpp"
#include "System/Systems.hpp"
#include "../Display/MyLib.hpp"

namespace MyComponents
{
    struct DrawableSprite
    {
        std::shared_ptr<sf::Texture> texture;
        std::shared_ptr<sf::Sprite> back;
        std::shared_ptr<sf::Clock> m_clock;
    };

    struct Scrolling
    {
        float scroll_value;
    };

    struct DrawableSprite_x
    {
        std::shared_ptr<sf::Texture> texture;
        std::shared_ptr<sf::Sprite> back;
        std::shared_ptr<sf::Clock> m_clock;
        int state;
    };

    struct Scrolling_x
    {
        float scroll_value;
    };

    struct Bullet
    {
        std::shared_ptr<sf::Texture> texture;
        std::shared_ptr<sf::Sprite> back;
        std::shared_ptr<sf::Clock> m_clock;
        int shot;
        float x;
        float y;
    };

    class MoveBullet
    {
    public:
        /**
         * @brief Construct a new Draw Sprite System object
         *
         * @param window
         * @param lib
         */
        MoveBullet(sf::RenderWindow &window, MyLib &lib) : _win(window), _lib(lib) {}

        /**
         * @brief Destroy the Draw Sprite System object
         *
         */
        ~MoveBullet(){};
        sf::RenderWindow &_win;
        MyLib &_lib;

        /**
         * @brief Draw a sprite
         *
         * @param r
         */
        void drawing_shape(Registry &r)
        {
            auto &drawable = r.get_components<Bullet>();
            auto &positions = r.get_components<Position>();
            auto &control = r.get_components<Controllable>();
            // std::cout << "ok" << std::endl;

            for (size_t i = 0; i < drawable.size() && i < positions.size() && i < control.size(); ++i)
            {
                auto &draw = drawable[i];
                auto &pos = positions[i];
                auto &ctrl = control[i];
                if (draw && pos && ctrl)
                {
                    auto shape(draw.value().back);
                    // auto shape(draw.value().back);
                    auto clock(draw.value().m_clock);
                    sf::Time time = _lib.ElapsedTime(clock);
                    if ((int)(time.asMicroseconds()) > 1)
                    {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) == true && draw.value().shot == 0)
                        {
                            // std::cout << "ok" << std::endl;
                            draw.value().x = 140 + positions[i].value()._position.first;
                            draw.value().y = 85 + positions[i].value()._position.second;
                            _lib.setPosition(shape, (sf::Vector2f){draw.value().x, draw.value().y});
                            // sprite_x.setPosition(sf::Vector2f(sprite.getPosition().x + 80, sprite.getPosition().y + 80));
                            draw.value().shot = 1;
                        }
                        if (draw.value().shot != 0)
                        {
                            // get = sprite_x.getPosition();
                            draw.value().x += 3;
                            _lib.setPosition(shape, (sf::Vector2f){draw.value().x, draw.value().y});
                            _lib.draw_sprites(_win, shape);
                            // sprite_x.setPosition(get);
                        }
                        if (draw.value().x >= 1300)
                        {
                            draw.value().x = 140 + positions[i].value()._position.first;
                            draw.value().y = 85 + positions[i].value()._position.second;
                            _lib.setPosition(shape, (sf::Vector2f){draw.value().x, draw.value().y});
                            // sprite_x.setPosition(sf::Vector2f(sprite.getPosition().x + 80, sprite.getPosition().y + 80));
                            draw.value().shot = 0;
                        }
                        time = _lib.ClockRestart(clock);
                    }
                }
            }
        }
    };

    class DrawSpriteSystem
    {
        public:

            /**
             * @brief Construct a new Draw Sprite System object
             *
             * @param window
             * @param lib
             */
            DrawSpriteSystem(sf::RenderWindow &window, MyLib &lib) : _win(window), _lib(lib){}

            /**
             * @brief Destroy the Draw Sprite System object
             *
             */
            ~DrawSpriteSystem(){};
            sf::RenderWindow &_win;
            MyLib &_lib;

            /**
             * @brief Draw a sprite
             *
             * @param r
             */
            void drawing_shape(Registry &r) {
                auto &drawable = r.get_components<DrawableSprite>();
                auto &positions = r.get_components<Position>();

                for (size_t i = 0; i < drawable.size() && i < positions.size(); ++ i) {
                    auto &draw = drawable[i];
                    auto &pos = positions[i];
                    if (draw && pos) {
                        auto shape(draw.value().back);
                        // auto shape(draw.value().back);
                        float one = positions[i].value()._position.first;
                        float two = positions[i].value()._position.second;
                        // std::cout << i << "dPos : " << one << std::endl;
                        _lib.setPosition(shape, (sf::Vector2f){one, two});
                        _lib.draw_sprites(_win, shape);
                    }
                }
            }
    };

    class ScrollingClass
    {
        public:

            /**
             * @brief Construct a new Scrolling Class object
             *
             * @param lib
             */
            ScrollingClass(MyLib &lib) : _lib(lib){}

            /**
             * @brief Destroy the Scrolling Class object
             *
             */
            ~ScrollingClass(){};
            MyLib &_lib;

            /**
             * @brief Establish the scrolling of the parallax background
             *
             * @param r
             */
            void ScrollingSystem(Registry &r) {
                auto &positions = r.get_components<Position>();
                auto &scrolling = r.get_components<Scrolling>();
                auto &drawable = r.get_components<DrawableSprite>();

                for (size_t i = 0; i < positions.size() && i < scrolling.size() && i < drawable.size(); ++ i) {
                    auto &pos = positions[i];
                    auto const &scr = scrolling[i];
                    auto const &draw = drawable[i];
                    if (pos && scr && draw) {
                        auto clock(draw.value().m_clock);
                        sf::Time time = _lib.ElapsedTime(clock);
                        if ((int)(time.asMilliseconds()) > 130) {
                            if (pos.value()._position.first <= -1300)
                                pos.value()._position.first = 0;
                            else
                                pos.value()._position.first -= scr.value().scroll_value;
                            time = _lib.ClockRestart(clock);
                        }
                    }
                }
            }
    };

    class DrawEnemySystem
    {
    public:
        /**
         * @brief Construct a new Draw Sprite System object
         *
         * @param window
         * @param lib
         */
        DrawEnemySystem(sf::RenderWindow &window, MyLib &lib) : _win(window), _lib(lib) {}

        /**
         * @brief Destroy the Draw Sprite System object
         *
         */
        ~DrawEnemySystem(){};
        sf::RenderWindow &_win;
        MyLib &_lib;

        /**
         * @brief Draw a sprite
         *
         * @param r
         */
        void drawing_shape(Registry &r)
        {
            auto &drawable = r.get_components<DrawableSprite_x>();
            auto &positions = r.get_components<Position>();
            auto &bullets = r.get_components<Bullet>();

            for (size_t i = 0; i < drawable.size() && i < positions.size(); ++i)
            {
                auto &draw = drawable[i];
                auto &pos = positions[i];
                auto &bull = bullets[0];
                if (draw && pos)
                {
                    sf::FloatRect rect1 = (*draw.value().back).getGlobalBounds();
                    // for (size_t j = 0; j < bullets.size(); ++ j) {
                    sf::FloatRect rect2 = (*bull.value().back).getGlobalBounds();
                    //}
                    if (rect1.intersects(rect2))
                    {
                        std::cout << "touched" << std::endl;
                        draw.value().state += 1;
                    }
                    auto shape(draw.value().back);
                    // auto shape(draw.value().back);
                    float one = positions[i].value()._position.first;
                    float two = positions[i].value()._position.second;
                    // std::cout << i << "dPos : " << one << std::endl;
                    _lib.setPosition(shape, (sf::Vector2f){one, two});
                    if (draw.value().state < 2)
                        _lib.draw_sprites(_win, shape);
                }
            }
        }
    };

    class MoveEnemy
    {
        public:

            /**
             * @brief Construct a new Scrolling Class object
             *
             * @param lib
             */
            MoveEnemy(MyLib &lib) : _lib(lib){}

            /**
             * @brief Destroy the Scrolling Class object
             *
             */
            ~MoveEnemy(){};
            MyLib &_lib;

            /**
             * @brief Establish the scrolling of the parallax background
             *
             * @param r
             */
            void MoveEnemySystem(Registry &r) {
                auto &positions = r.get_components<Position>();
                auto &scrolling = r.get_components<Scrolling_x>();
                auto &drawable = r.get_components<DrawableSprite_x>();

                for (size_t i = 0; i < positions.size() && i < scrolling.size() && i < drawable.size(); ++ i) {
                    auto &pos = positions[i];
                    auto const &scr = scrolling[i];
                    auto const &draw = drawable[i];
                    if (pos && scr && draw) {
                        auto clock(draw.value().m_clock);
                        sf::Time time = _lib.ElapsedTime(clock);
                        if ((int)(time.asMilliseconds()) > 130) {
                            if (pos.value()._position.first <= -500)
                                pos.value()._position.first = 1400;
                            else
                                pos.value()._position.first -= scr.value().scroll_value;
                            time = _lib.ClockRestart(clock);
                        }
                    }
                }
            }
    };

    class Menu
    {
    public:
        Menu(sf::RenderWindow &_window, MyLib &lib, sf::IntRect _rect, sf::IntRect _rect2, sf::IntRect _rect3, sf::IntRect _rect4, sf::IntRect _rect5, sf::IntRect _rect6) : window(_window), _lib(lib), rect(_rect), rect2(_rect2), rect3(_rect3), rect4(_rect4), rect5(_rect5), rect6(_rect6)
        {
            i = 0, level = 0, x = 0, y = 0, volume = 100, n = 0, play = 0;

            buffer.loadFromFile("menu/Intro.ogg");
            sound.setBuffer(buffer);
            sound.play();
            sprite.setPosition(x, y);
            texture.loadFromFile("menu/space1.png");
            sprite.setTexture(texture);

            svessel.setPosition(1180, 600);
            tvessel.loadFromFile("menu/vaisseau.png");
            svessel.setTexture(tvessel);
            svessel.setScale(0.15, 0.15);

            svessel_anim.setPosition(1366 / 2.45, 100);
            tvessel_anim.loadFromFile("menu/vessel_anim.png");
            svessel_anim.setTexture(tvessel_anim);

            svessel2_anim.setPosition(1366 / 5.17, 360);
            tvessel2_anim.loadFromFile("menu/vessel2_anim.png");
            svessel2_anim.setTexture(tvessel2_anim);

            svessel3_anim.setPosition(1366 / 1.45, 360);
            tvessel3_anim.loadFromFile("menu/vessel2_anim.png");
            svessel3_anim.setTexture(tvessel3_anim);

            svessel4_anim.setPosition(1366 / 1.45, 400);
            tvessel4_anim.loadFromFile("menu/vessel2_anim.png");
            svessel4_anim.setTexture(tvessel4_anim);

            svessel5_anim.setPosition(1366 / 1.45, 380);
            tvessel5_anim.loadFromFile("menu/vessel3_anim.png");
            svessel5_anim.setTexture(tvessel5_anim);
            svessel5_anim.setScale(2, 2);

            sexit_anim.setPosition(1366 / 2.5, 370);
            texit_anim.loadFromFile("menu/exit.png");
            sexit_anim.setTexture(texit_anim);
            sexit_anim.setScale(2, 2);

            ttuto.loadFromFile("menu/tuto.png");
            stuto.setTexture(ttuto);

            if (!ftitle.loadFromFile("menu/ti.ttf"))
                ;
            if (!fplay.loadFromFile("menu/pol.TTF"))
                ;
            if (!fhow.loadFromFile("menu/pol.TTF"))
                ;
            if (!fsettings.loadFromFile("menu/pol.TTF"))
                ;
            if (!fquit.loadFromFile("menu/pol.TTF"))
                ;
            if (!fselect.loadFromFile("menu/pol.TTF"))
                ;
            if (!fsolo.loadFromFile("menu/pol.TTF"))
                ;
            if (!fmulti.loadFromFile("menu/pol.TTF"))
                ;
            if (!fsure.loadFromFile("menu/pol.TTF"))
                ;
            if (!fyes.loadFromFile("menu/pol.TTF"))
                ;
            if (!fno.loadFromFile("menu/pol.TTF"))
                ;
            if (!fwant.loadFromFile("menu/pol.TTF"))
                ;
            if (!fvol.loadFromFile("menu/pol.TTF"))
                ;
            if (!ffps.loadFromFile("menu/pol.TTF"))
                ;
            if (!fdif.loadFromFile("menu/pol.TTF"))
                ;
            if (!fintens.loadFromFile("menu/pol.TTF"))
                ;
            if (!fchoose.loadFromFile("menu/pol.TTF"))
                ;

            ttitle.setFont(ftitle);
            ttitle.setString("R- TYPE");
            ttitle.setCharacterSize(24);
            ttitle.setFillColor(sf::Color::Red);
            ttitle.setOutlineColor(sf::Color::Cyan);
            ttitle.setOutlineThickness(1.4);
            ttitle.setStyle(sf::Text::Bold);
            ttitle.setPosition(1366 / 2.8, 40);
            ttitle.setScale(2, 2);

            tplay.setFont(fplay);
            tplay.setString("PLAY");
            tplay.setCharacterSize(24);
            tplay.setFillColor(sf::Color::Magenta);
            tplay.setStyle(sf::Text::Bold);
            tplay.setPosition(1366 / 2.30, 320);
            tplay.setScale(0.5, 0.5);

            thow.setFont(fhow);
            thow.setString("HOW TO PLAY");
            thow.setCharacterSize(24);
            thow.setFillColor(sf::Color::Magenta);
            thow.setStyle(sf::Text::Bold);
            thow.setPosition(1366 / 2.75, 390);
            thow.setScale(1, 1);

            tsettings.setFont(fsettings);
            tsettings.setString("SETTINGS");
            tsettings.setCharacterSize(24);
            tsettings.setFillColor(sf::Color::Magenta);
            tsettings.setStyle(sf::Text::Bold);
            tsettings.setPosition(1366 / 2.80, 480);
            tsettings.setScale(1.5, 1.5);

            tquit.setFont(fquit);
            tquit.setString("QUIT");
            tquit.setCharacterSize(24);
            tquit.setFillColor(sf::Color::Magenta);
            tquit.setStyle(sf::Text::Bold);
            tquit.setPosition(1366 / 2.55, 570);
            tquit.setScale(2, 2);

            tselect.setFont(fselect);
            tselect.setString("SELECT MODE");
            tselect.setCharacterSize(24);
            tselect.setFillColor(sf::Color::Cyan);
            tselect.setStyle(sf::Text::Bold);
            tselect.setOutlineColor(sf::Color::Magenta);
            tselect.setOutlineThickness(1.4);
            tselect.setPosition(1366 / 2.65, 120);

            tsolo.setFont(fsolo);
            tsolo.setString("SOLO");
            tsolo.setCharacterSize(24);
            tsolo.setFillColor(sf::Color::Magenta);
            tsolo.setStyle(sf::Text::Bold);
            tsolo.setPosition(1366 / 5, 270);

            tmulti.setFont(fmulti);
            tmulti.setString("MULTI PLAYER");
            tmulti.setCharacterSize(24);
            tmulti.setFillColor(sf::Color::Magenta);
            tmulti.setStyle(sf::Text::Bold);
            tmulti.setPosition(1366 / 1.57, 270);

            tsure.setFont(fsure);
            tsure.setString("ARE YOU SURE");
            tsure.setCharacterSize(24);
            tsure.setFillColor(sf::Color::Magenta);
            tsure.setStyle(sf::Text::Bold);
            tsure.setPosition(1366 / 2.65, 120);

            tyes.setFont(fyes);
            tyes.setString("YES");
            tyes.setCharacterSize(24);
            tyes.setFillColor(sf::Color::Magenta);
            tyes.setStyle(sf::Text::Bold);
            tyes.setPosition(1366 / 5, 370);

            tno.setFont(fno);
            tno.setString("NO");
            tno.setCharacterSize(24);
            tno.setFillColor(sf::Color::Magenta);
            tno.setStyle(sf::Text::Bold);
            tno.setPosition(1366 / 1.40, 370);

            twant.setFont(fwant);
            twant.setString("CHANGE SOMETHING");
            twant.setCharacterSize(24);
            twant.setFillColor(sf::Color::Magenta);
            twant.setStyle(sf::Text::Bold);
            twant.setPosition(1366 / 3, 120);

            tvol.setFont(fvol);
            tvol.setString("VOLUME");
            tvol.setCharacterSize(24);
            tvol.setFillColor(sf::Color::Magenta);
            tvol.setStyle(sf::Text::Bold);
            tvol.setPosition(1366 / 5.5, 280);

            tfps.setFont(ffps);
            tfps.setString("FPS");
            tfps.setCharacterSize(24);
            tfps.setFillColor(sf::Color::Magenta);
            tfps.setStyle(sf::Text::Bold);
            tfps.setPosition(1366 / 5.5, 380);

            tdif.setFont(fdif);
            tdif.setString("DIFFICULTY");
            tdif.setCharacterSize(24);
            tdif.setFillColor(sf::Color::Magenta);
            tdif.setStyle(sf::Text::Bold);
            tdif.setPosition(1366 / 5.5, 480);

            tintens.setFont(fintens);
            tintens.setString(std::to_string(volume).c_str());
            tintens.setCharacterSize(24);
            tintens.setFillColor(sf::Color::Cyan);
            tintens.setStyle(sf::Text::Bold);
            tintens.setPosition(1366 / 3, 280);

            tchoose.setFont(fchoose);
            tchoose.setString(vec[i]);
            tchoose.setCharacterSize(24);
            tchoose.setFillColor(sf::Color::Cyan);
            tchoose.setStyle(sf::Text::Bold);
            tchoose.setPosition(1366 / 2.5, 480);
        }
        ~Menu() {};
        void drawMenu()
        {
            my_mouse = sf::Mouse::getPosition();
            sound.setLoop(true);

            if ((my_mouse.x >= 665 && my_mouse.x <= 710) && (my_mouse.y >= 387 && my_mouse.y <= 401))
            {
                tplay.setFillColor(sf::Color::Cyan);
            }
            else
                tplay.setFillColor(sf::Color::Magenta);
            if ((my_mouse.x >= 569 && my_mouse.x <= 806) && (my_mouse.y >= 461 && my_mouse.y <= 480))
            {
                thow.setFillColor(sf::Color::Cyan);
            }
            else
                thow.setFillColor(sf::Color::Magenta);
            if ((my_mouse.x >= 559 && my_mouse.x <= 824) && (my_mouse.y >= 552 && my_mouse.y <= 584))
            {
                tsettings.setFillColor(sf::Color::Cyan);
            }
            else
                tsettings.setFillColor(sf::Color::Magenta);
            if ((my_mouse.x >= 607 && my_mouse.x <= 766) && (my_mouse.y >= 644 && my_mouse.y <= 689))
            {
                tquit.setFillColor(sf::Color::Cyan);
            }
            else
                tquit.setFillColor(sf::Color::Magenta);
            if ((my_mouse.x >= 1262 && my_mouse.x <= 1331) && (my_mouse.y >= 676 && my_mouse.y <= 714))
            {
                svessel.setScale(0.17, 0.17);
            }
            else
                svessel.setScale(0.15, 0.15);
            if ((my_mouse.x >= 665 && my_mouse.x <= 710) && (my_mouse.y >= 387 && my_mouse.y <= 401) && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
            {
                n = 1;
            }
            if ((my_mouse.x >= 569 && my_mouse.x <= 806) && (my_mouse.y >= 461 && my_mouse.y <= 480) && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
            {
                n = 2;
            }
            if ((my_mouse.x >= 559 && my_mouse.x <= 824) && (my_mouse.y >= 552 && my_mouse.y <= 584) && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
            {
                n = 3;
            }
            if ((my_mouse.x >= 607 && my_mouse.x <= 766) && (my_mouse.y >= 644 && my_mouse.y <= 689) && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
            {
                n = 4;
            }
            if ((my_mouse.x >= 1262 && my_mouse.x <= 1331) && (my_mouse.y >= 676 && my_mouse.y <= 714) && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
            {
                n = 5;
            }
            time = clock.getElapsedTime();
            seconds = time.asMicroseconds() / 500000;
            if (seconds > 0.1f)
            {
                if (rect.left <= 200)
                    rect.left += 100;
                else
                    rect.left = 0;
                clock.restart();
            }
            if (x >= -1366)
            {
                x -= 0.2;
            }
            else if (x <= -1366)
            {
                x = 0;
            }
            sprite.setPosition(x, y);
            window.clear();
            if (n == 0)
            {
                window.draw(sprite);
                window.draw(ttitle);
                window.draw(tplay);
                window.draw(thow);
                window.draw(tsettings);
                window.draw(tquit);
                window.draw(svessel);
                window.draw(svessel_anim);
                svessel_anim.setTextureRect(rect);
            }
            if (n == 1)
            {
                if ((my_mouse.x >= 345 && my_mouse.x <= 435) && (my_mouse.y >= 339 && my_mouse.y <= 360))
                {
                    tsolo.setOutlineColor(sf::Color::Cyan);
                    tsolo.setOutlineThickness(1.4);
                    time2 = clock2.getElapsedTime();
                    seconds2 = time2.asMicroseconds() / 500000;
                    if (seconds2 > 0.0000001f)
                    {
                        if (rect2.left <= 200)
                            rect2.left += 100;
                        else
                            rect2.left = 0;
                        clock2.restart();
                    }
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
                    {
                        play = 19;
                    }
                }
                else
                    tsolo.setOutlineThickness(0);
                if ((my_mouse.x >= 941 && my_mouse.x <= 1211) && (my_mouse.y >= 339 && my_mouse.y <= 363))
                {
                    tmulti.setOutlineColor(sf::Color::Cyan);
                    tmulti.setOutlineThickness(1.4);
                    time3 = clock3.getElapsedTime();
                    seconds3 = time3.asMicroseconds() / 500000;
                    if (seconds3 > 0.0000001f)
                    {
                        if (rect3.left <= 200)
                            rect3.left += 100;
                        else
                            rect3.left = 0;
                        clock3.restart();
                    }
                    time4 = clock4.getElapsedTime();
                    seconds4 = time4.asMicroseconds() / 500000;
                    if (seconds4 > 0.0000001f)
                    {
                        if (rect4.left <= 200)
                            rect4.left += 100;
                        else
                            rect4.left = 0;
                        clock4.restart();
                    }
                }
                else
                    tmulti.setOutlineThickness(0);
                window.draw(sprite);
                window.draw(tselect);
                window.draw(tsolo);
                window.draw(tmulti);
                window.draw(svessel2_anim);
                window.draw(svessel3_anim);
                window.draw(svessel4_anim);
                svessel2_anim.setTextureRect(rect2);
                svessel3_anim.setTextureRect(rect3);
                svessel4_anim.setTextureRect(rect4);
            }
            if (n == 2)
            {
                window.draw(stuto);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    n = 0;
            }
            if (n == 3)
            {
                window.draw(sprite);
                window.draw(twant);
                window.draw(tvol);
                window.draw(tfps);
                window.draw(tdif);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    volume = volume -= 0.001;
                    sound.setVolume(volume);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    volume = volume += 0.001;
                    sound.setVolume(volume);
                }
                if (volume > 100)
                    volume = 100;
                if (volume < 0)
                    volume = 0;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    tchoose.setString(vec[i--]);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                {
                    tchoose.setString(vec[i++]);
                }
                if (i > 2)
                    i = 2;
                if (i < 0)
                    i = 0;
                if (i == 1)
                    level = 1;
                if (i == 2)
                    level = 2;
                if (i == 3)
                    level = 3;
                time5 = clock5.getElapsedTime();
                seconds5 = time5.asMicroseconds() / 500000;
                if (seconds5 > 0.1f)
                {
                    if (rect5.left <= 840)
                        rect5.left += 60;
                    else
                        rect5.left = 0;
                    clock5.restart();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    n = 0;
                tintens.setString(std::to_string(volume).c_str());
                window.draw(tintens);
                window.draw(tchoose);
                window.draw(svessel5_anim);
                svessel5_anim.setTextureRect(rect5);
            }
            if (n == 4)
            {
                time6 = clock6.getElapsedTime();
                seconds6 = time6.asMicroseconds() / 500000;
                if (seconds6 > 0.00000001f)
                {
                    if (rect6.left <= 1100)
                        rect6.left += 100;
                    else
                        rect6.left = 0;
                    clock6.restart();
                }
                if ((my_mouse.x >= 345 && my_mouse.x <= 415) && (my_mouse.y >= 439 && my_mouse.y <= 461))
                {
                    tyes.setOutlineColor(sf::Color::Cyan);
                    tyes.setOutlineThickness(1.4);
                }
                else
                    tyes.setOutlineThickness(0);
                if ((my_mouse.x >= 1046 && my_mouse.x <= 1090) && (my_mouse.y >= 438 && my_mouse.y <= 459))
                {
                    tno.setOutlineColor(sf::Color::Cyan);
                    tno.setOutlineThickness(1.4);
                }
                else
                    tno.setOutlineThickness(0);
                if ((my_mouse.x >= 1046 && my_mouse.x <= 1090) && (my_mouse.y >= 438 && my_mouse.y <= 459) && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
                    n = 0;
                if ((my_mouse.x >= 345 && my_mouse.x <= 415) && (my_mouse.y >= 439 && my_mouse.y <= 461) && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
                    window.close();
                window.draw(sprite);
                window.draw(tsure);
                window.draw(tyes);
                window.draw(tno);
                window.draw(sexit_anim);
                sexit_anim.setTextureRect(rect6);
            }
            if (n == 5)
            {
                int z;
                int k;
                if (z <= -2000)
                    z = 0;
                scredits.setPosition(k, z);
                window.draw(scredits);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    n = 0;
            }
            std::cout << "n = " << n << std::endl;
            window.display();
        };
        int level;
        int play;

    private:
        MyLib _lib;
        int n = 0;
        sf::RenderWindow &window; //(sf::VideoMode(1366, 768), "SFML works!");
        sf::Text ttitle;
        sf::Font ftitle;
        sf::Text tplay;
        sf::Font fplay;
        sf::Text thow;
        sf::Font fhow;
        sf::Text tsettings;
        sf::Font fsettings;
        sf::Text tquit;
        sf::Font fquit;
        sf::Text tselect;
        sf::Font fselect;
        sf::Text tsolo;
        sf::Font fsolo;
        sf::Text tmulti;
        sf::Font fmulti;
        sf::Text tsure;
        sf::Font fsure;
        sf::Text tyes;
        sf::Font fyes;
        sf::Text tno;
        sf::Font fno;
        sf::Text tvol;
        sf::Font fvol;
        sf::Text tfps;
        sf::Font ffps;
        sf::Text twant;
        sf::Font fwant;
        sf::Text tdif;
        sf::Font fdif;
        sf::Text tintens;
        sf::Font fintens;
        sf::Text tchoose;
        sf::Font fchoose;
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Texture tvessel;
        sf::Sprite svessel;
        sf::Texture tvessel_anim;
        sf::Sprite svessel_anim;
        sf::Texture tvessel2_anim;
        sf::Sprite svessel2_anim;
        sf::Texture tvessel3_anim;
        sf::Sprite svessel3_anim;
        sf::Texture tvessel4_anim;
        sf::Sprite svessel4_anim;
        sf::Texture tcredits;
        sf::Sprite scredits;
        sf::Texture ttuto;
        sf::Sprite stuto;
        sf::Texture tvessel5_anim;
        sf::Sprite svessel5_anim;
        sf::Texture texit_anim;
        sf::Sprite sexit_anim;
        sf::IntRect rect;  //(0, 0, 100, 100);
        sf::IntRect rect2; //(0, 0, 100, 26);
        sf::IntRect rect3; //(0, 0, 100, 26);
        sf::IntRect rect4; //(0, 0, 100, 26);
        sf::IntRect rect5; //(0, 0, 60, 30);
        sf::IntRect rect6; //(0, 0, 100, 38);
        sf::SoundBuffer buffer;
        sf::Sound sound;
        std::vector<std::string> vec = {"EASY", "MEDIUM", "HARD"};
        sf::Time time;
        float seconds;
        sf::Clock clock;
        sf::Time time2;
        float seconds2;
        sf::Clock clock2;
        sf::Time time3;
        float seconds3;
        sf::Clock clock3;
        sf::Time time4;
        float seconds4;
        sf::Clock clock4;
        sf::Time time5;
        float seconds5;
        sf::Clock clock5;
        sf::Time time6;
        float seconds6;
        sf::Clock clock6;
        sf::Vector2i my_mouse;
        int i;
        float volume;
        float x;
        float y;
        float scroll_credit;
    };
}

#endif /* !PARALLAX_HPP_ */
