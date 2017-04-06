#include "constructed2.h"
#include "gr3d.h"
#include <list>
#include <stdio.h>
#include <math.h>

using namespace std;

Vertex::Vertex(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}
Vertex::Vertex(float p, float q, Plane plane)
{
	switch(plane)
	{
	case Plane::XY:
		x = p;
		y = q;
		z = 0;
		break;
	case Plane::XZ:
		x = p;
		y = 0;
		z = q;
		break;
	case Plane::YZ:
		x = 0;
		y = p;
		z = q;
		break;
	}
}
float Vertex::get(Axis axis) const
{
	switch(axis)
	{
	case Axis::X:
		return x;
	case Axis::Y:
		return y;
	case Axis::Z:
		return z;
	}
}
void Vertex::set(float p, Axis axis)
{
	switch(axis)
	{
	case Axis::X:
		x = p;
		return;
	case Axis::Y:
		y = p;
		return;
	case Axis::Z:
		z = p;
		return;
	}
}
Vertex Vertex::translate(float p, Axis axis) const
{
	Vertex v = *this;
	v.set(p+v.get(axis), axis);
	return v;
}
Vertex Vertex::translate(const Vector &v) const
{
	return Vertex(x+v.x, y+v.y, z+v.z);
}
Vertex Vertex::rotateX(float angle) const
{
	return Vertex(x, y*cos(angle)-z*sin(angle), z*cos(angle)+y*sin(angle));
}
Vertex Vertex::rotateY(float angle) const
{
	return Vertex(x*cos(angle)-z*sin(angle), y, z*cos(angle)+x*sin(angle));
}
Vertex Vertex::rotateZ(float angle) const
{
	return Vertex(x*cos(angle)-y*sin(angle), y*cos(angle)+x*sin(angle), z);
}
void Vertex::print() const
{
	printf("%f %f %f\n", x, y, z);
}

 

static void renderTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, struct Color &c)
{
	addTriangle(v1.x, v1.y, v1.z,   v2.x, v2.y, v2.z, v3.x, v3.y, v3.z, &c);
}
void Polygon::render(struct Color &c) const
{
	if(vertexes.size() < 3)
	{
		printf("ERROR: Polygon::render(): vertexes.size() < 3\n");
		return;
	}
	list<Vertex>::const_iterator it1=vertexes.begin();
	list<Vertex>::const_iterator it2=vertexes.begin();
	list<Vertex>::const_iterator it3=vertexes.begin();
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
Polygon Polygon::revertVertexSequence() const
{
	Polygon p;
	for(list<Vertex>::const_reverse_iterator it=vertexes.rbegin(); it!=vertexes.rend(); it++)
		p.vertexes.push_back(*it);
	return p;
}
Polygon Polygon::translate(float p, Axis axis) const
{
	Polygon ret;
	for(const Vertex &v : vertexes)
		ret.vertexes.push_back(v.translate(p, axis));
	return ret;
}
Polygon Polygon::translate(const Vector &v) const
{
	Polygon p;
	for(list<Vertex>::const_iterator it=vertexes.begin(); it!=vertexes.end(); it++)
		p.vertexes.push_back(it->translate(v));
	return p;
}
Polygon Polygon::rotateX(float angle) const
{
        Polygon p;
        for(list<Vertex>::const_iterator it=vertexes.begin(); it!=vertexes.end(); it++)
                p.vertexes.push_back(it->rotateX(angle));
        return p;
}
Polygon Polygon::rotateY(float angle) const
{
        Polygon p;
        for(list<Vertex>::const_iterator it=vertexes.begin(); it!=vertexes.end(); it++)
                p.vertexes.push_back(it->rotateY(angle));
        return p;
}
Polygon Polygon::rotateZ(float angle) const
{
        Polygon p;
        for(list<Vertex>::const_iterator it=vertexes.begin(); it!=vertexes.end(); it++)
                p.vertexes.push_back(it->rotateZ(angle));
        return p;
}
Polygon Polygon::adjust(Axis axis, Adjust a, float p) const
{
	float min = vertexes.front().get(axis);
	float max = min;
	
	for(const Vertex &v : vertexes)
	{
		float f = v.get(axis);
		if(f<min)
			min = f;
		if(f>max)
			max = f;
	}	
	switch(a)
	{
	case Adjust::MIN:
		return translate(p-min, axis);
	case Adjust::MAX:
		return translate(p-max, axis);
	case Adjust::CENTER:
		return translate(p-(max+min)/2, axis);
	}
}
void Polyhedron::render(struct Color &c) const
{
	for(list<Polygon>::const_iterator it=faces.begin(); it!=faces.end(); it++)
		it->render(c);
}
Polyhedron Polyhedron::translate(float p, Axis axis) const
{
	Polyhedron ret;
	for(const Polygon &f : faces)
		ret.faces.push_back(f.translate(p, axis));
	return ret;
}
Polyhedron Polyhedron::translate(const Vector &v) const
{
	Polyhedron p;
	for(list<Polygon>::const_iterator it=faces.begin(); it!=faces.end(); it++)
		p.faces.push_back(it->translate(v));
	return p;
}
Polyhedron Polyhedron::rotateX(float angle) const
{
	Polyhedron p;
	for(list<Polygon>::const_iterator it=faces.begin(); it!=faces.end(); it++)
		p.faces.push_back(it->rotateX(angle));
	return p;
}
Polyhedron Polyhedron::rotateY(float angle) const
{
	Polyhedron p;
	for(list<Polygon>::const_iterator it=faces.begin(); it!=faces.end(); it++)
		p.faces.push_back(it->rotateY(angle));
	return p;
}
Polyhedron Polyhedron::rotateZ(float angle) const
{
	Polyhedron p;
	for(list<Polygon>::const_iterator it=faces.begin(); it!=faces.end(); it++)
		p.faces.push_back(it->rotateZ(angle));
	return p;
}
Polyhedron Polyhedron::adjust(Axis axis, Adjust a, float p) const
{
        float min = faces.front().vertexes.front().get(axis);
        float max = min;
	
	for(const Polygon &p : faces)
	{
	        for(const Vertex &v : p.vertexes)
	        {
        	        float f = v.get(axis);
                	if(f<min)
                        	min = f;
	                if(f>max)
        	                max = f;
	        }
	}
	switch(a)
	{
	case Adjust::MIN:
		return translate(p-min, axis);
	case Adjust::MAX:
		return translate(p-max, axis);
	case Adjust::CENTER:
		return translate(p-(max+min)/2, axis);
	}
}

Polygon mkIsoscelesTriangle(float base, float height, Plane plane)
{
	Polygon p;
	p.vertexes.push_back(Vertex(-base/2,      0, plane));
	p.vertexes.push_back(Vertex( base/2,      0, plane));
	p.vertexes.push_back(Vertex(      0, height, plane));
	return p;
}
Polygon mkRectangleZ(float sizeX, float sizeY)
{
	Polygon p;
	p.vertexes.push_back(Vertex(-sizeX/2, -sizeY/2, 0));
	p.vertexes.push_back(Vertex( sizeX/2, -sizeY/2, 0));
	p.vertexes.push_back(Vertex( sizeX/2,  sizeY/2, 0));
	p.vertexes.push_back(Vertex(-sizeX/2,  sizeY/2, 0));
	return p;
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
Polygon mkParallelogram(const Vertex &base1, const Vertex &base2, const Vector &baseTranslation)
{
	Polygon p;
	p.vertexes.push_back(base1);
	p.vertexes.push_back(base2);
	p.vertexes.push_back(base2.translate(baseTranslation));
	p.vertexes.push_back(base1.translate(baseTranslation));

	return p;
}

Polyhedron mkPrism(const Polygon &base, const Vector &baseTranslation)
{
	Polyhedron p;

	if(base.vertexes.size() < 3)
	{
		printf("ERROR: mkPrism(): base.vertexes.size() < 3\n");
		return p;
	}

	p.faces.push_back(base.revertVertexSequence());
	p.faces.push_back(base.translate(baseTranslation));
	p.faces.push_back(mkParallelogram(base.vertexes.back(), base.vertexes.front(), baseTranslation));

	list<Vertex>::const_iterator it1=base.vertexes.begin();
	list<Vertex>::const_iterator it2=base.vertexes.begin();
	it2 ++;

	while(it2 != base.vertexes.end())
	{
		p.faces.push_back(mkParallelogram(*it1, *it2, baseTranslation));
		it1 ++;
		it2 ++;
	}

	return p;
}
Polyhedron mkCuboid(float sizeX, float sizeY, float sizeZ)
{
	return mkPrism(mkRectangleZ(sizeX, sizeY).translate(Vector(0, 0, -sizeZ/2)), Vector(0, 0, sizeZ));
	
}
Polyhedron mkCuboid(float x1, float x2, float y1, float y2, float z1, float z2)
{
	return mkPrism(mkRectangleZ(x1, x2, y1, y2, z1), Vector(0, 0, z2));
}

