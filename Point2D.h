#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Point2D
{
public:
    Point2D();
    Point2D(double x, double y);
    ~Point2D();

    sf::Vector2f GetVector();
    void SetVector(sf::Vector2f vector);

    Point2D operator+(const Point2D& point2D);
    Point2D operator-(const Point2D& point2D);
    Point2D operator*(float number);
    Point2D operator/(float number);

    Point2D& operator=(const Point2D& point2D);

    Point2D& operator+=(const Point2D& point2D);
    Point2D& operator-=(const Point2D& point2D);
    Point2D& operator*=(float number);
    Point2D& operator/=(float number);

    float sqrAbs();
private:
    double x;
    double y;
};
