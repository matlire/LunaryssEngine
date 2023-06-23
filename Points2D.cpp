#include "Points2D.h"

using namespace std;

Points2D::Points2D(float scale, vector<Point2D> points, Point2D position)
{
	this->points = points;
	this->position = position;
	this->scale = scale;
}