#ifndef __GR_3_D__H__
#define __GR_3_D__H__


void addTriangle(float x1, float y1, float z1, 
		 float x2, float y2, float z2, 
		 float x3, float y3, float z3, 
		 float r1, float g1, float b1, 
		 float r2, float g2, float b2, 
		 float r3, float g3, float b3);

void triangles2vertexes();

void processTriangles(unsigned int vertexbufferId, unsigned int colorBufferId);

#endif
