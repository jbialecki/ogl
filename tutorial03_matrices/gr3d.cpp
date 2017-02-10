#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <list>
#include <vector>
#include <math.h>
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <common/shader.hpp>

#define FLOATS_PER_VERTEX 3
#define VORTICES_PER_LINE 2
#define VORTICES_PER_TRIANGLE 3

using namespace glm;
using namespace std;

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


list<Triangle> g_triangles;
vector<float> g_triangles_vertexes;
vector<float> g_triangles_colours;

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
void processTriangles(unsigned int vertexbufferId, unsigned int colorBufferId)
{
        processPrimitives(vertexbufferId, colorBufferId, &g_triangles_vertexes[0], &g_triangles_colours[0], g_triangles.size(), VORTICES_PER_TRIANGLE, GL_TRIANGLES);
}



