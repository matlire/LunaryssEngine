#include "Point2D.h"

using namespace std;


Point2D::Point2D()
{
    this->x = 0;
    this->y = 0;
    
}

Point2D::Point2D(double x, double y)
{
	this->x = x;
	this->y = y;
}

Point2D::~Point2D()
{

}

sf::Vector2f Point2D::GetVector()
{
    return sf::Vector2f(this->x, this->y);
}

Point2D Point2D::operator+(const Point2D& point2D)
{
    return Point2D{ this->x + point2D.x, this->y + point2D.y };
}

Point2D Point2D::operator-(const Point2D& point2D)
{
    return Point2D{ this->x - point2D.x, this->y - point2D.y };
}

Point2D Point2D::operator*(float number)
{
    return Point2D{ this->x * number, this->y * number };
}

Point2D Point2D::operator/(float number)
{
    return Point2D{ this->x * number, this->y * number };
}

Point2D& Point2D::operator=(const Point2D& point2D)
{
    this->x = point2D.x;
    this->y = point2D.y;
    return *this;
}

Point2D& Point2D::operator+=(const Point2D& point2D)
{
    this->x += point2D.x;
    this->y += point2D.y;
    return *this;
}

Point2D& Point2D::operator-=(const Point2D& point2D)
{
    this->x -= point2D.x;
    this->y -= point2D.y;
    return *this;
}

Point2D& Point2D::operator*=(float number)
{
    this->x *= number;
    this->y *= number;
    return *this;
}

Point2D& Point2D::operator/=(float number)
{
    this->x /= number;
    this->y /= number;
    return *this;
}

float Point2D::sqrAbs()
{
    return x * x + y * y;
}

void Point2D::SetVector(sf::Vector2f vector)
{
    this->x = vector.x;
    this->y = vector.y;
}