#ifndef __GR_3_D__H__
#define __GR_3_D__H__


struct Color
{
	float r;
	float g;
	float b;
};

void addLine(	 float x1, float y1, float z1, 
		 float x2, float y2, float z2, 
		 float r1, float g1, float b1, 
		 float r2, float g2, float b2); 

void addLine(	 float x1, float y1, float z1,
                 float x2, float y2, float z2,
		 struct Color *c);

void addTriangle(float x1, float y1, float z1, 
		 float x2, float y2, float z2, 
		 float x3, float y3, float z3, 
		 float r1, float g1, float b1, 
		 float r2, float g2, float b2, 
		 float r3, float g3, float b3);

void addTriangle(float x1, float y1, float z1,
                 float x2, float y2, float z2,
                 float x3, float y3, float z3,
		 struct Color *c);

void addLightVector(float x, float y, float z);

void addNormals(struct Color *c);

void triangles2vertexes();
void lines2vertexes();

void processLines(unsigned int vertexbufferId, unsigned int colorBufferId);
void processTriangles(unsigned int vertexbufferId, unsigned int colorBufferId);

#endif
