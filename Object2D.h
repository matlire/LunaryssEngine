#pragma once

#include <vector>
#include "Point2D.h"
#include "Points2D.h"
#include "settings.h"
#include "Ray.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace std;

class Object2D
{
public:
	Object2D(float scale, Point2D position = { 0, 0 }, vector<Point2D> points = {});
	~Object2D();

	void SetPosition(Point2D position);
	void SetPoints2D(vector<Point2D> points2D);
	void Draw(sf::RenderTarget& window);
	vector<Point2D> GetPoints2D();
private:
	vector<Point2D> points2D;
	Point2D position;
	float scale;
	sf::ConvexShape shape;
};