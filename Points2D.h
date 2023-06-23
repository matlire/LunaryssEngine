#pragma once

#include "Point2D.h"
#include <vector>

using namespace std;

class Points2D
{
public:
	Points2D(float scale, vector<Point2D> points = {}, Point2D position = {0, 0});
private:
	vector<Point2D> points;
	Point2D position;
	float scale;
};