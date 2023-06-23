// https://habr.com/ru/articles/703500/

#include <iostream>
#include <SFML/Graphics.hpp>
#include "settings.h"

#include "Object2D.h"
#include "Point2D.h"
#include "World.h"
#include "Camera.h"
#include "Player.h"
#include "Time.h"

using namespace std;

int main()
{
    Time time;

    sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Game", sf::Style::Close);
    window.setFramerateLimit(60);

    Player player(P_RADIUS, P_COLOR, P_POSITION, P_POINTS, P_MSPEED, P_RSPEED);

    World world(G_WIDTH, G_HEIGHT);

    vector<Point2D> s_points = { Point2D(0, 0), Point2D(0, 1), Point2D(1, 1), Point2D(1, 0) };
    Object2D square1(50, Point2D(400, 50), s_points);
    s_points = { Point2D(0, 0), Point2D(0, 1), Point2D(1, 1) };
    Object2D triangle1(50, Point2D(100, 200), s_points);
    s_points = { Point2D(0, 0), Point2D(0, 1), Point2D(1, 1), Point2D(1, 0) };
    Object2D square2(50, Point2D(500, 200), s_points);
    s_points = { Point2D(0, 1), Point2D(1, 1), Point2D(1, 0) };
    Object2D triangle2(50, Point2D(350, 300), s_points);
    s_points = { Point2D(1, 0), Point2D(2, 0), Point2D(3, 1), Point2D(2, 2), Point2D(1, 2), Point2D(0, 1) };
    Object2D super1(35, Point2D(100, 300), s_points);
    s_points = { Point2D(1, 0), Point2D(2, 0), Point2D(3, 1), Point2D(2, 2), Point2D(1, 2), Point2D(0, 1.5), Point2D(0, 0.5) };
    Object2D super2(35, Point2D(200, 100), s_points);

    s_points = { Point2D(0, 0), Point2D(0, 10), Point2D(640, 10), Point2D(640, 0) };
    Object2D paral1(1, Point2D(0, 0), s_points);
    s_points = { Point2D(0, 0), Point2D(-10, 0), Point2D(-10, 480), Point2D(0, 480) };
    Object2D paral2(1, Point2D(640, 0), s_points);
    s_points = { Point2D(0, 0), Point2D(10, 0), Point2D(10, 480), Point2D(0, 480) };
    Object2D paral3(1, Point2D(0, 0), s_points);
    s_points = { Point2D(0, 0), Point2D(0, -10), Point2D(640, -10), Point2D(640, 0) };
    Object2D paral4(1, Point2D(0, 480), s_points);

    world.AddObject2D(triangle1);
    world.AddObject2D(square1);
    world.AddObject2D(triangle2);
    world.AddObject2D(square2);
    world.AddObject2D(super1);
    world.AddObject2D(super2);

    world.AddObject2D(paral1);
    world.AddObject2D(paral2);
    world.AddObject2D(paral3);
    world.AddObject2D(paral4);

    Camera camera(player, world, P_R_FOV, DEPTH, P_RAY_NUM, W_HEIGHT, M_PROJ_K, M_DIST, P_SCALE, EYE_CORR);

    while (window.isOpen())
    {
        time.Update();
        double elapsedTime = time.GetDeltaTime();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        camera.Input(elapsedTime, window);
        camera.Handle(window);
        camera.EndFrameProcessing();
        
        window.display();
        window.clear();
    }

    return 0;
}