#pragma once

#include <SFML/Graphics.hpp>
#include "Point2D.h"
#include <vector>
#include "Object2D.h"

using namespace std;

class World
{
public:
	World(int width, int height);
	World();
	void Draw(sf::RenderTarget& window);
	void AddObject2D(Object2D object);
	vector<Object2D> GetMap();
private:
	int width;
	int height;
	vector<Object2D> map;
};