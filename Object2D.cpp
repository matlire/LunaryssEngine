#include "Object2D.h"

using namespace std;

Object2D::Object2D(float scale, Point2D position, vector<Point2D> points)
{
	this->scale = scale;
	this->position = position;
	int i = 0;
	for (auto p : points)
	{
		this->points2D.push_back((p*this->scale) + this->position);
	}
}

Object2D::~Object2D()
{}

void Object2D::SetPosition(Point2D position)
{
	this->position = position;
}

void Object2D::SetPoints2D(vector<Point2D> points2D)
{
	this->points2D = points2D;
}

vector<Point2D> Object2D::GetPoints2D()
{
	return this->points2D;
}

void Object2D::Draw(sf::RenderTarget& window)
{
	sf::ConvexShape points;
	points.setPointCount(GetPoints2D().size());
	int i = 0;
	for (auto p : this->points2D)
	{
		points.setPoint(i++, p.GetVector());
	}
	points.setOutlineColor(O_OUTLINE_COLOR);
	points.setFillColor(O_FILL_COLOR);
	points.setOutlineThickness(O_OUTLINE_THICKNESS);

	this->shape = points;
	window.draw(points);
}
