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
	

void addOrientedCuboid( float x1, float x2,
                        float y1, float y2,
                        float z1, float z2,
                        struct Color *c)
{
	addOrientedRectangleX(x1, y2, y1, z1, z2, c);
	addOrientedRectangleX(x2, y1, y2, z1, z2, c);
	addOrientedRectangleY(x1, x2, y1, z1, z2, c);
	addOrientedRectangleY(x2, x1, y2, z1, z2, c);
	addOrientedRectangleZ(x2, x1, y1, y2, z1, c);
	addOrientedRectangleZ(x1, x2, y1, y2, z2, c);
}
void addOrientedPyramidZ(       float x1, float x2,
                                float y1, float y2,
                                float z_base, float z_top,
                                struct Color *c)
{
	float top_x = (x1+x2)/2.;
	float top_y = (y1+y2)/2.;

	addOrientedRectangleZ(x2, x1, y1, y2, z_base, c);

	addTriangle(x1, y1, z_base, x2, y1, z_base, top_x, top_y, z_top, c);
	addTriangle(x2, y1, z_base, x2, y2, z_base, top_x, top_y, z_top, c);
	addTriangle(x2, y2, z_base, x1, y2, z_base, top_x, top_y, z_top, c);
	addTriangle(x1, y2, z_base, x1, y1, z_base, top_x, top_y, z_top, c);
}
