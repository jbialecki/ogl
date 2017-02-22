#include "constructed.h"

void addOrientedRectangleX(	float x,
				float y1, float y2,
				float z1, float z2,
				struct Color *c)
{
	addTriangle(x, y1, z1,   x, y2, z1,   x, y2, z2,   c);
	addTriangle(x, y1, z1,   x, y2, z2,   x, y1, z2,   c);
}

void addOrientedRectangleY(	float x1,  float x2, 
	                        float y,
        	                float z1, float z2,
                	        struct Color *c)
{
	addTriangle(x1, y, z1,   x2, y, z1,   x2, y, z2,   c);
	addTriangle(x1, y, z1,   x2, y, z2,   x1, y, z2,   c);
}

void addOrientedRectangleZ(	float x1, float x2,  
	                        float y1, float y2,
        	                float z,
                	        struct Color *c)
{
	addTriangle(x1, y1, z,   x2, y1, z,   x2, y2, z,   c);
	addTriangle(x1, y1, z,   x2, y2, z,   x1, y2, z,   c);
}
	

