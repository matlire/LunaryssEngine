#include "Player.h"

using namespace std;

Player::Player(double radius, sf::Color color, Point2D position, int points, double walkSpeed, double rotateSpeed)
{
	this->radius = radius;
	this->position = position;
	this->color = color;
	this->points = points;
	this->walkSpeed = walkSpeed;
	this->rotateSpeed = rotateSpeed;
}

Player::Player()
{
	this->radius = 1;
	this->position = Point2D(0, 0);
	this->color = sf::Color(255, 255, 255);
	this->points = 30;
	this->walkSpeed = 1.0;
	this->rotateSpeed = 1.0;
}

void Player::Draw(sf::RenderTarget& window)
{
	sf::CircleShape pCircle (this->radius, this->points);
	pCircle.setFillColor(this->color);
	pCircle.setPosition(this->position.GetVector().x, this->position.GetVector().y);
	window.draw(pCircle);
}

void Player::SetPos(Point2D position)
{
	this->position = position;
}