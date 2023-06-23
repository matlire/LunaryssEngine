#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Point2D.h"
#include "settings.h"
#include <vector>

class Ray
{
public:
	Ray(Point2D startPoint, double depth, double direction);
	sf::VertexArray GetLine();
	void SetEnd(Point2D point);
	Point2D GetEnd();
	Point2D GetStart();
private:
	Point2D startPoint;
	Point2D endPoint;
};