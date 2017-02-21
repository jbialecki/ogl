#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <vector>
#include <math.h>
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <common/shader.hpp>
#include "gr3d.h"

#define FLOATS_PER_VERTEX 3
#define VORTICES_PER_LINE 2
#define VORTICES_PER_TRIANGLE 3

using namespace glm;
using namespace std;

class Line
{
public:
        float x1, y1, z1;
        float x2, y2, z2;
        float r1, g1, b1;
        float r2, g2, b2;
};
class Triangle
{
public:
        float x1, y1, z1;
        float x2, y2, z2;
        float x3, y3, z3;
        float r1, g1, b1;
        float r2, g2, b2;
        float r3, g3, b3;
};
class Vect
{
public:
	float x, y, z;
};


list<Triangle> g_triangles;
list<Line> g_lines;

vector<float> g_triangles_vertexes;
vector<float> g_triangles_colours;

vector<float> g_lines_vertexes;
vector<float> g_lines_colours;

void getNormal(const Triangle &in, Vect &out)
{
	Vect a, b;	// edges
	float len;

	a.x = in.x2 - in.x1;
	a.y = in.y2 - in.y1;
	a.z = in.z2 - in.z1;

	b.x = in.x3 - in.x1;
	b.y = in.y3 - in.y1;
	b.z = in.z3 - in.z1;

	out.x = a.y*b.z - a.z*b.y;
	out.y = a.z*b.x - a.x*b.z;
	out.z = a.x*b.y - a.y*b.x;

	len = sqrt(out.x*out.x + out.y*out.y + out.z*out.z);

	out.x /= len;
	out.y /= len;
	out.z /= len;
}

void addTriangle(float x1, float y1, float z1, 
                 float x2, float y2, float z2,
                 float x3, float y3, float z3,
                 float r1, float g1, float b1,
                 float r2, float g2, float b2,
                 float r3, float g3, float b3)
{
	Triangle t;
	memcpy(&t.x1, &x1, 18*sizeof(float));
	g_triangles.push_back(t);
}
void addLine(	 float x1, float y1, float z1, 
                 float x2, float y2, float z2,
                 float r1, float g1, float b1,
                 float r2, float g2, float b2)
{
	Line l;
	memcpy(&l.x1, &x1, 12*sizeof(float));
	g_lines.push_back(l);
}
void addTriangle(float x1, float y1, float z1,
                 float x2, float y2, float z2,
                 float x3, float y3, float z3,
                 struct Color *c)
{
	if(c == NULL)
	{
		printf("ERROR: addTriangle(color==NULL)\n");
	}
	addTriangle(	x1, y1, z1,
			x2, y2, z2,
			x3, y3, z3,
			c->r, c->g, c->b,
			c->r, c->g, c->b,
			c->r, c->g, c->b
		);
}
void addLine(float x1, float y1, float z1,
                 float x2, float y2, float z2,
                 struct Color *c)
{
	if(c == NULL)
	{
		printf("ERROR: addLine(color==NULL)\n");
	}
	addLine(	x1, y1, z1,
			x2, y2, z2,
			c->r, c->g, c->b,
			c->r, c->g, c->b
		);
}


void triangles2vertexes()
{
        g_triangles_vertexes.assign(g_triangles.size()*9, 0.0);
        g_triangles_colours.assign(g_triangles.size()*9, 0.0);
        int i=0;
        for(list<Triangle>::iterator it = g_triangles.begin(); it != g_triangles.end(); it++)
        {
                memcpy(&g_triangles_vertexes[i], &it->x1, 9*sizeof(float));
                memcpy(&g_triangles_colours[i], &it->r1, 9*sizeof(float));
                i += 9;
        }
}
void lines2vertexes()
{
        g_lines_vertexes.assign(g_lines.size()*6, 0.0);
        g_lines_colours.assign(g_lines.size()*6, 0.0);
        int i=0;
        for(list<Line>::iterator it = g_lines.begin(); it != g_lines.end(); it++)
        {
                memcpy(&g_lines_vertexes[i], &it->x1, 6*sizeof(float));
                memcpy(&g_lines_colours[i], &it->r1, 6*sizeof(float));
                i += 6;
        }
}
void processPrimitives(int vertexbufferId, int colorBufferId, const float *vertexBuff, const float *colorBuff, int primitive_count, int vortices_per_primitive, int primitive_type)
{
        if(primitive_count == 0)
                return;
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbufferId);
        glBufferData(
                        GL_ARRAY_BUFFER,
                        primitive_count * vortices_per_primitive * FLOATS_PER_VERTEX * sizeof(float),
                        vertexBuff,
                        GL_STATIC_DRAW
                );
        glVertexAttribPointer(
                        0,                  // layout
                        FLOATS_PER_VERTEX,  // floats per vertex
                        GL_FLOAT,           // type
                        GL_FALSE,           // normalized?
                        0,                  // stride
                        (void*)0            // array buffer offset
                );

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
        glBufferData(
                        GL_ARRAY_BUFFER,
                        primitive_count * vortices_per_primitive * FLOATS_PER_VERTEX * sizeof(float),
                        colorBuff,
                        GL_STATIC_DRAW
                );
        glVertexAttribPointer(
                        1,                  // layout
                        FLOATS_PER_VERTEX,  // floats per vertex
                        GL_FLOAT,           // type
                        GL_FALSE,           // normalized?
                        0,                  // stride
                        (void*)0            // array buffer offset
                );
        glDrawArrays(
                        primitive_type,
                        0,                                              // idx of first vertex in buffer
                        primitive_count * vortices_per_primitive        // number of vortices
                );
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
}
void processLines(unsigned int vertexbufferId, unsigned int colorBufferId)
{
        processPrimitives(vertexbufferId, colorBufferId, &g_lines_vertexes[0], &g_lines_colours[0], g_lines.size(), VORTICES_PER_LINE, GL_LINES);
}
void processTriangles(unsigned int vertexbufferId, unsigned int colorBufferId)
{
        processPrimitives(vertexbufferId, colorBufferId, &g_triangles_vertexes[0], &g_triangles_colours[0], g_triangles.size(), VORTICES_PER_TRIANGLE, GL_TRIANGLES);
}



