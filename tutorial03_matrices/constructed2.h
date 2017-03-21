#ifndef __CONSTRUCTED2__H__
#define __CONSTRUCTED2__H__

#include <list>

struct Color;

class Vertex
{
public:
	Vertex(float _x, float _y, float _z);
	void print();
	float x, y, z;
};

class Polygon
{
public:
	std::list<Vertex> vertexes;
	void render(struct Color &c);
};

class Polyhedron
{
public:
	std::list<Polygon> faces;
	void render(struct Color &c);
};


Polygon mkRectangleZ(float x1, float x2, float y1, float y2, float z);

#endif
