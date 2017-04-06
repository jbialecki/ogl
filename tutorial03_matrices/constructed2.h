#ifndef __CONSTRUCTED2__H__
#define __CONSTRUCTED2__H__

#include <list>

#define Pi 3.14159

struct Color;
class Vertex;
typedef Vertex Vector;

enum class Axis
{
	X, Y, Z
};
enum class Plane
{
	XY, XZ, YZ
};
enum class Adjust
{
	MIN, CENTER, MAX
};

class Vertex
{
public:
	Vertex(float _x, float _y, float _z);
	Vertex(float p, float q, Plane plane);
	float get(Axis axis) const;
	void set(float p, Axis axis);
	Vertex translate(float p, Axis axis) const;
	Vertex translate(const Vector &v) const;
	Vertex rotateX(float angle) const;
	Vertex rotateY(float angle) const;
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
	Polygon translate(float p, Axis axis) const;
	Polygon translate(const Vector &v) const;
	Polygon rotateX(float angle) const;
	Polygon rotateY(float angle) const;
	Polygon rotateZ(float angle) const;
	Polygon adjust(Axis axis, Adjust adjust, float p) const;
};

class Polyhedron
{
public:
	std::list<Polygon> faces;
	void render(struct Color &c) const;
	Polyhedron translate(float p, Axis axis) const;
	Polyhedron translate(const Vector &v) const;
	Polyhedron rotateX(float angle) const;
	Polyhedron rotateY(float angle) const;
	Polyhedron rotateZ(float angle) const;
	Polyhedron adjust(Axis axis, Adjust adjust, float p) const;
};

Polygon mkIsoscelesTriangle(float base, float height, Plane plane); // trójkąt równoramienny

Polygon mkRectangleZ(float sizeX, float sizeY); // prostokat z plaszczyznie Z symetryczny wzgl srodka ukladu wspolrzednych
Polygon mkRectangleZ(float x1, float x2, float y1, float y2, float z); // prostokat z plaszczyznie Z

Polygon mkParallelogram(const Vertex &base1, const Vertex &base2, const Vector &baseTranslation); // rownoleglobok


Polyhedron mkPrism(const Polygon &base, const Vector &baseTranslation); // graniastoslup

Polyhedron mkCuboid(float sizeX, float sizeY, float sizeZ); // prostopadloscian symetryczny wzgl srodka ukladu wspolrzednych
Polyhedron mkCuboid(float x1, float x2, float y1, float y2, float z1, float z2); // prostopadloscian

#endif
