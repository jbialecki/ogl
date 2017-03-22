#ifndef __CONSTRUCTED2__H__
#define __CONSTRUCTED2__H__

#include <list>

struct Color;
class Vertex;
typedef Vertex Vector;

class Vertex
{
public:
	Vertex(float _x, float _y, float _z);
	Vertex translate(const Vector &v) const;
	Vertex rotateZ(float angle) const;
	void print() const;
	float x, y, z;
};


class Polygon
{
public:
	std::list<Vertex> vertexes;
	void render(struct Color &c) const;
	Polygon revertVertexSequence() const;
	Polygon translate(const Vector &v) const;
	Polygon rotateZ(float angle) const;
};

class Polyhedron
{
public:
	std::list<Polygon> faces;
	void render(struct Color &c) const;
	Polyhedron translate(const Vector &v) const;
	Polyhedron rotateZ(float angle) const;
};


Polygon mkRectangleZ(float sizeX, float sizeY); // prostokat z plaszczyznie Z symetryczny wzgl srodka ukladu wspolrzednych
Polygon mkRectangleZ(float x1, float x2, float y1, float y2, float z); // prostokat z plaszczyznie Z

Polygon mkParallelogram(const Vertex &base1, const Vertex &base2, const Vector &baseTranslation); // rownoleglobok


Polyhedron mkPrism(const Polygon &base, const Vector &baseTranslation); // graniastoslup

Polyhedron mkCuboid(float sizeX, float sizeY, float sizeZ); // prostopadloscian symetryczny wzgl srodka ukladu wspolrzednych
Polyhedron mkCuboid(float x1, float x2, float y1, float y2, float z1, float z2); // prostopadloscian

#endif
