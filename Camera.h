#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Point2D.h"
#include "Player.h"
#include "World.h"
#include <vector>
#include "Ray.h"
#include <math.h>

using namespace std;

struct FrameInfo
{
	double direction;
	double angle;
	Point2D position;
};

class Camera
{
public:
	Camera(Player& player, World& world, double radFov, int depth, int rayNum, int windowHeight, double projK, double sDist, int pScale, bool eyeC);

	void StartFrameProcessing();
	void EndFrameProcessing();

	bool Input(double elapsedTime, sf::RenderWindow& window);
	void Handle(sf::RenderTarget& window);
	bool OnSegment(Point2D p, Point2D q, Point2D r);
	double Orientation(Point2D p, Point2D q, Point2D r);
	bool DoIntersect(Point2D p1, Point2D q1, Point2D p2, Point2D q2);
	void IntersectionPoint(Point2D p1, Point2D q1, Point2D p2, Point2D q2, Point2D& intersection);
	double Degree2Rad(double degree);
	double Rad2Degree(double rad);
private:
	bool hadFocus = false;

	double directionSin = 0;
	double directionCos = 0;
	double direction = 0;
	double angle;
	double radFov;
	int depth;
	int rayNum;
	int windowHeight;
	double projK;
	bool map = false;
	double sDist;
	int pScale;
	bool eyeC = false;

	FrameInfo oldFrame, curFrame;
	Player player;
	World world;
	vector<Ray> rays;

	void Shift(Point2D vector);
};