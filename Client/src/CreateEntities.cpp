/*
** EPITECH PROJECT, 2022
** B-CPP-500-COT-5-1-rtype-prunella.dousso
** File description:
** CreateEntities
*/

#include "Client/include/CreateEntities.hpp"

extern struct all_connexions c_connect;

void registerComponentType(Registry &r)
{
    r.register_component<MyComponents::Position>();
    r.register_component<MyComponents::Velocity>();
    r.register_component<MyComponents::Drawable>();
    r.register_component<MyComponents::Controllable>();
    r.register_component<MyComponents::DrawableSprite>();
    r.register_component<MyComponents::DrawableSprite_x>();
    r.register_component<MyComponents::Scrolling_x>();
    r.register_component<MyComponents::Scrolling>();
    r.register_component<MyComponents::MyId>();
    r.register_component<MyComponents::PlayerId>();
    r.register_component<MyComponents::Bullet>();
}

void create_component_me(Registry &r, MyLib &lib, std::string file, sf::Vector2f pos)
{
    const entity_t &player = r.spawn_entity();
    struct MyComponents::Bullet bullet = {lib.LoadTexture("assets/ParallaxAssets/bullet.png"), lib.create_sprite(bullet.texture), std::make_shared<sf::Clock>(), 0, 0, 0};
    struct MyComponents::Drawable drawn_obj = {lib.LoadTexture(file), lib.create_sprite(drawn_obj.texture)};
    struct MyComponents::Controllable remote = {sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down};
    struct MyComponents::MyId my_id = {size_t(c_connect.connected)};
    r.add_component<MyComponents::Position>(player, MyComponents::Position(pos.x, pos.y));
    r.add_component<MyComponents::Velocity>(player, MyComponents::Velocity(0, 0));
    r.add_component<MyComponents::Drawable>(player, drawn_obj);
    r.add_component<MyComponents::Controllable>(player, remote);
    r.add_component<MyComponents::MyId>(player, my_id);
    r.add_component<MyComponents::Bullet>(player, bullet);
}

void create_component_players(Registry &r, MyLib &lib, std::string file, sf::Vector2f pos, size_t id)
{
    const entity_t &player = r.spawn_entity();
    struct MyComponents::Drawable drawn_obj = {lib.LoadTexture(file), lib.create_sprite(drawn_obj.texture)};
    struct MyComponents::PlayerId id_p = {id};
    r.add_component<MyComponents::Position>(player, MyComponents::Position(pos.x, pos.y));
    r.add_component<MyComponents::Drawable>(player, drawn_obj);
    r.add_component<MyComponents::PlayerId>(player, id_p);
}

void create_component_parallax(Registry &r, MyLib &lib, std::string file, float s)
{
    const entity_t &parallax = r.spawn_entity();
    struct MyComponents::DrawableSprite drawn = {lib.LoadTexture(file), lib.create_sprite(drawn.texture), std::make_shared<sf::Clock>()};
    struct MyComponents::Scrolling scroll = {s};
    r.add_component<MyComponents::Position>(parallax, MyComponents::Position(00.f, 00.f));
    r.add_component<MyComponents::DrawableSprite>(parallax, drawn);
    r.add_component<MyComponents::Scrolling>(parallax, scroll);
}

/*void create_component_sound(Registry &r, MyLib &lib, std::string file)
{
    //"Client/src/parallax1.png"
    const entity_t &parallax = r.spawn_entity();
    sf::Sound sound;
    struct MyComponents::Sound sound = {lib.loadFromFile(file), sound};
    r.add_component<MyComponents::Sound>(parallax, scroll);
}*/

void create_component_enemy(Registry &r, MyLib &lib, std::string file)
{
    const entity_t &enemy = r.spawn_entity();
    struct MyComponents::DrawableSprite_x drawn = {lib.LoadTexture(file), lib.create_sprite(drawn.texture), std::make_shared<sf::Clock>(), 0};
    struct MyComponents::Scrolling_x scroll = {5};
    r.add_component<MyComponents::Position>(enemy, MyComponents::Position(1000.f, 00.f));
    r.add_component<MyComponents::DrawableSprite_x>(enemy, drawn);
    r.add_component<MyComponents::Scrolling_x>(enemy, scroll);
}

void initialize_parallax(Registry &r, MyLib &lib)
{
    int s = 5;
    std::vector<std::string> backgrounds = {"assets/ParallaxAssets/parallax1_back.png", "assets/ParallaxAssets/parallax2_stars.png", "assets/ParallaxAssets/parallax3_astro.png", "assets/ParallaxAssets/parallax4_saturn.png"};

    for (int i = 0; i < 4; i++) {
        create_component_parallax(r, lib, backgrounds[i], s);
        s += 5;
    }
}
