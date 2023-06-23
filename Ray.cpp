#include "Ray.h"

Ray::Ray(Point2D startPoint, double depth, double direction)
{
    sf::Vector2f calcVector;
    calcVector.x = startPoint.GetVector().x + depth * cos(PI * 2 - direction);
    calcVector.y = startPoint.GetVector().y - depth * sin(PI * 2 - direction);

    Point2D endPoint = Point2D(calcVector.x, calcVector.y);

    this->startPoint = startPoint;
    this->endPoint = endPoint;
}

sf::VertexArray Ray::GetLine()
{
    sf::VertexArray rayLine(sf::Lines, 2);

    rayLine[0].color = sf::Color(255, 255, 255);
    rayLine[0].position = sf::Vector2f(this->startPoint.GetVector());
    rayLine[1].color = sf::Color(255, 255, 255);
    rayLine[1].position = sf::Vector2f(this->endPoint.GetVector());

    return rayLine;
}

void Ray::SetEnd(Point2D point)
{
    this->endPoint = point;
}

Point2D Ray::GetEnd()
{
    return this->endPoint;
}

Point2D Ray::GetStart()
{
    return this->startPoint;
}
