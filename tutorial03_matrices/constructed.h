#ifndef __CONSTRUCTED__H__
#define __CONSTRUCTED__H__

#include "gr3d.h"

void addOrientedRectangleX(	float x,
	                        float y1, float y2,
	                        float z1, float z2,
	                        struct Color *c);

void addOrientedRectangleY(	float x1, float x2, 
				float y,
                	        float z1, float z2,
                        	struct Color *c);

void addOrientedRectangleZ(	float x1, float x2, 
				float y1, float y2,
        	                float z,
                	        struct Color *c);

void addOrientedCuboid(	float x1, float x2,
			float y1, float y2,
			float z1, float z2,
			struct Color *c);
#endif
