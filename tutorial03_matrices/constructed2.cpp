#include "constructed2.h"
#include "gr3d.h"
#include <list>
#include <stdio.h>

using namespace std;

Vertex::Vertex(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}
void Vertex::print()
{
	printf("%f %f %f\n", x, y, z);
}

 

static void renderTriangle(Vertex &v1, Vertex &v2, Vertex &v3, struct Color &c)
{
	addTriangle(v1.x, v1.y, v1.z,   v2.x, v2.y, v2.z, v3.x, v3.y, v3.z, &c);
}
void Polygon::render(struct Color &c)
{
	if(vertexes.size() < 3)
	{
		printf("ERROR: Polygon::render(): vertexes.size() < 3\n");
		return;
	}
	list<Vertex>::iterator it1=vertexes.begin();
	list<Vertex>::iterator it2=vertexes.begin();
	list<Vertex>::iterator it3=vertexes.begin();
	it2++;
	it3++;
	it3++;
	
	while(it3 != vertexes.end())
	{
		renderTriangle(*it1, *it2, *it3, c);
		it2++;
		it3++;
	}
}

Polygon mkRectangleZ(float x1, float x2, float y1, float y2, float z)
{
	Polygon p;
	p.vertexes.push_back(Vertex(x1, y1, z));
	p.vertexes.push_back(Vertex(x2, y1, z));
	p.vertexes.push_back(Vertex(x2, y2, z));
	p.vertexes.push_back(Vertex(x1, y2, z));
	return p;
}

