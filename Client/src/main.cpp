/*
** EPITECH PROJECT, 2022
** B-CPP-500-COT-5-1-rtype-prunella.dousso
** File description:
** Main
*/

#include "../include/System/Systems.hpp"
#include "Client/include/CreateEntities.hpp"

extern struct all_connexions c_connect;

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
        NetWorkClient myClient(atoi(av[1]), av[2]);
        registerComponentType(bigBrowser);
        sf::RenderWindow window(sf::VideoMode(1300, 731), "My window");
        sf::Event event;
        /*initialisation*/
        initialize_parallax(bigBrowser, lib);
        create_component_enemy(bigBrowser, lib, "assets/graphics/players_enemies/e_alien.png");
        /*initialization des classes créées pour les systèmes*/
        MyComponents::DrawSystem ball(window, lib);
        MyComponents::DrawSpriteSystem parallax(window, lib);
        MyComponents::ScrollingClass scr_class(lib);
        MyComponents::DrawEnemySystem enemy(window, lib);
        MyComponents::MoveEnemy move(lib);
        MyComponents::MoveSystem motion(event);
        MyComponents::PosiSystem _position(&myClient);
        MyComponents::MoveBullet bullet(window, lib);
        sf::IntRect rect(0, 0, 100, 100);
        sf::IntRect rect2(0, 0, 100, 26);
        sf::IntRect rect3(0, 0, 100, 26);
        sf::IntRect rect4(0, 0, 100, 26);
        sf::IntRect rect5(0, 0, 60, 30);
        sf::IntRect rect6(0, 0, 100, 38);
        MyComponents::Menu menu(window, lib, rect, rect2, rect3, rect4, rect5, rect6);

        myClient.Connection_and_initialize();
        std::unique_lock<std::mutex> lk(c_connect.myMutex);
        std::thread myThread_2(&NetWorkClient::MsgLoop, &myClient);
        c_connect.cv.wait(lk);
        /*Créer chaque joueur dans sa map*/
        create_component_me(bigBrowser, lib, glob::ShipFiles[c_connect.connected], glob::ShipPos[c_connect.connected]);
        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                motion.VelocitySystem(bigBrowser);
                if (event.type == sf::Event::Closed) {
                    window.close();
                    myClient.DeconnectionHost();
                    exit(0);
                }
            }
            window.clear(sf::Color::White);
            /*Systèmes pour faire bouger les entités*/
            if (menu.play != 19)
            {
                menu.play = 19;
            }
            else
            {
                _position.PositionSystem(bigBrowser);
                /*Recevoir les informations des autres joueurs et les récréer dans la map, maybe dans une fonction*/
                /*Appeler le système de position des autres joueurs*/
                //c_connect.OtherPlayers[myClient.id_others] = sf::Vector2f(myClient.posX_others, myClient.posY_others);
                //create_component_players(bigBrowser, lib, glob::ShipFiles[myClient.id_others], c_connect.OtherPlayers[myClient.id_others], myClient.id_others);
                MyComponents::PlayerPositionSystem(bigBrowser);
                scr_class.ScrollingSystem(bigBrowser);
                move.MoveEnemySystem(bigBrowser);
                parallax.drawing_shape(bigBrowser);
                ball.drawing_shape(bigBrowser);
                enemy.drawing_shape(bigBrowser);
            }
            window.display();
        }
        myThread_2.join();
    }
    return 0;
}
