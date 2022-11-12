/*
** EPITECH PROJECT, 2022
** B-CPP-500-COT-5-1-rtype-prunella.dousso
** File description:
** Main
*/

#include "../include/System/Systems.hpp"
#include "../include/Parallax.hpp"
#include "../includes/Client.hpp"

/**
 * @brief Register Component in the right sparse arrays
 *
 * @param r
 */
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
    r.register_component<MyComponents::Bullet>();
    //r.register_component<MyComponents::Menu>();
}

/**
 * @brief Create a component circle/player object
 *
 * @param r
 * @param lib
 * @param file
 */

/*void create_menu(Registry &r, MyLib &lib)
{
    const entity_t &menu = r.spawn_entity();

    struct MyComponents::Menu slide = {lib.LoadTexture("menu/space1.png"), lib.create_sprite(slide.texture), lib.LoadTexture("menu/vaisseau.png"), lib.create_sprite(slide.tvessel),
    lib.LoadTexture("menu/vessel_anim.png"), lib.create_sprite(slide.tvessel_anim), lib.LoadTexture("menu/vessel2_anim.png"), lib.create_sprite(slide.tvessel2_anim),
    lib.LoadTexture("menu/vessel2_anim.png"), lib.create_sprite(slide.tvessel3_anim), lib.LoadTexture("menu/vessel2_anim.png"), lib.create_sprite(slide.tvessel4_anim),
    lib.LoadTexture("menu/vessel3_anim.png"), lib.create_sprite(slide.tvessel5_anim), lib.LoadTexture("menu/exit.png"), lib.create_sprite(slide.texit),
    lib.LoadTexture("menu/tuto.png"), lib.create_sprite(slide.ttuto), lib.LoadFont("menu/title.ttf"), lib.create_text(slide.font, "toss")};
    r.add_component<MyComponents::Menu>(menu, slide);
}*/

void create_component_circle(Registry &r, MyLib &lib, std::string file)
{
    const entity_t &player = r.spawn_entity();
    struct MyComponents::Bullet bullet = {lib.LoadTexture("assets/ParallaxAssets/bullet.png"), lib.create_sprite(bullet.texture), std::make_shared<sf::Clock>(), 0, 0, 0};
    struct MyComponents::Drawable drawn_obj = {lib.LoadTexture(file), lib.create_sprite(drawn_obj.texture)};
    struct MyComponents::Controllable remote = {sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down};
    r.add_component<MyComponents::Position>(player, MyComponents::Position(30.f, 30.f));
    r.add_component<MyComponents::Velocity>(player, MyComponents::Velocity(0, 0));
    r.add_component<MyComponents::Drawable>(player, drawn_obj);
    r.add_component<MyComponents::Controllable>(player, remote);
    r.add_component<MyComponents::Bullet>(player, bullet);
}

/**
 * @brief Create a component parallax object
 *
 * @param r
 * @param lib
 * @param file
 * @param s
 */
void create_component_parallax(Registry &r, MyLib &lib, std::string file, float s)
{
    //"Client/src/parallax1.png"
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

/**
 * @brief Initialize the parallax
 *
 * @param r
 * @param lib
 */
void initialize_parallax(Registry &r, MyLib &lib)
{
    int s = 5;
    std::vector<std::string> backgrounds = {"assets/ParallaxAssets/parallax1_back.png", "assets/ParallaxAssets/parallax2_stars.png", "assets/ParallaxAssets/parallax3_astro.png", "assets/ParallaxAssets/parallax4_saturn.png"};

    for (int i = 0; i < 4; i++) {
        create_component_parallax(r, lib, backgrounds[i], s);
        s += 5;
    }
}

int main(int ac, char **av)
{
    if (ac != 3) {
        printf ("You must to use 2 arguments after binary to run server:\n");
        printf ("Usage:\n");
        printf ("First argument: Port (Number)\n");
        printf ("Second argument: address ip\n");
        return (84);
    }
    else {
        Registry bigBrowser;
        MyLib lib;
        sf::IntRect rect(0, 0, 100, 100);
        sf::IntRect rect2(0, 0, 100, 26);
        sf::IntRect rect3(0, 0, 100, 26);
        sf::IntRect rect4(0, 0, 100, 26);
        sf::IntRect rect5(0, 0, 60, 30);
        sf::IntRect rect6(0, 0, 100, 38);
        registerComponentType(bigBrowser);
        sf::RenderWindow window(sf::VideoMode(1300, 731), "My window");
        sf::Event event;
        MyComponents::Menu menu(window, lib, rect, rect2, rect3, rect4, rect5, rect6);
        //sf::Music music;
        /*initialisation*/
        create_component_circle(bigBrowser, lib, "assets/graphics/players_enemies/player1.png");
        initialize_parallax(bigBrowser, lib);
        create_component_enemy(bigBrowser, lib, "assets/graphics/players_enemies/e_alien.png");
//        create_menu(bigBrowser, lib);
        //music.openFromFile("assets/sounds/Intro.ogg");
        /*initialization des classes créées pour les systèmes*/
        MyComponents::DrawSystem ball(window, lib);
        MyComponents::DrawSpriteSystem parallax(window, lib);
        MyComponents::ScrollingClass scr_class(lib);
        MyComponents::DrawEnemySystem enemy(window, lib);
        MyComponents::MoveEnemy move(lib);
        MyComponents::MoveSystem motion(event);
        MyComponents::MoveBullet bull(window, lib);
//        MyComponents::DrawMenu menu(window, lib);


        NetWorkClient myClient(atoi(av[1]), av[2]);
        myClient.Connection_and_initialize();
        myClient.Client_LoopStart();

        std::thread myThread_2(&NetWorkClient::MsgLoop, &myClient);
        //music.setLoop(true);
        //music.play();
        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                if (menu.play == 19)
                    motion.VelocitySystem(bigBrowser);
                if (event.type == sf::Event::Closed) {
                    window.close();
                    exit(0);
                }
            }
            if (menu.play != 19)
                menu.drawMenu();
            else
            {
                window.clear(sf::Color::White);
                /*Systèmes pour faire bouger les entités*/
                MyComponents::PositionSystem(bigBrowser);
                scr_class.ScrollingSystem(bigBrowser);
                move.MoveEnemySystem(bigBrowser);
                /*Systèmes pour afficher*/
                parallax.drawing_shape(bigBrowser);
                ball.drawing_shape(bigBrowser);
                enemy.drawing_shape(bigBrowser);
                bull.drawing_shape(bigBrowser);
            }
            //window.clear(sf::Color::White);
            /*Systèmes pour faire bouger les entités*/
            //MyComponents::PositionSystem(bigBrowser);
            //scr_class.ScrollingSystem(bigBrowser);
            //move.MoveEnemySystem(bigBrowser);
            /*Systèmes pour afficher*/
            //parallax.drawing_shape(bigBrowser);
            //ball.drawing_shape(bigBrowser);
            //enemy.drawing_shape(bigBrowser);
            //bull.drawing_shape(bigBrowser);
//            menu.drawing_shape(bigBrowser);
            window.display();
        }
        myThread_2.join();
    }
    return 0;
}
