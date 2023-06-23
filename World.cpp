#include "World.h"

World::World(int width, int height)
{
    this->width = width;
    this->height = height;
}

World::World()
{
	this->width = 100;
	this->height = 100;
}

void World::AddObject2D(Object2D object)
{
    this->map.push_back(object);
}

void World::Draw(sf::RenderTarget& window)
{
	int i = 0;
	for (auto p : this->map)
	{
		this->map.at(i++).Draw(window);
	}
}

vector<Object2D> World::GetMap()
{
	return this->map;
}