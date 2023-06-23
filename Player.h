#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Point2D.h"

using namespace std;

class Player
{
public:
	Player(double radius, sf::Color color, Point2D position, int points, double walkSpeed, double rotateSpeed);
	Player();

	void Draw(sf::RenderTarget& window);
	void SetPos(Point2D position);
	Point2D GetPos() { return this->position; };
	Point2D GetRealPos() { return Point2D(this->position.GetVector().x + this->radius, this->position.GetVector().y + this->radius); }
	double GetWalkSpeed() { return this->walkSpeed; };
	double GetRotateSpeed() { return this->rotateSpeed; };
private:
	double radius;
	sf::Color color;
	Point2D position;
	int points;
	double walkSpeed;
	double rotateSpeed;
};