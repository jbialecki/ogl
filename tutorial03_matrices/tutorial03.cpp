// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include "gr3d.h"
#include "gr3d_ctx.h"
#include "constructed.h"


void getView_callback(Gr3dView &v)
{
        static float f = 0.0;
        f+= 0.002;
        v.camera_x = 30*sin(f);
        v.camera_y = 30*cos(f);
        v.camera_z = 20;
        v.lookAt_x = 0;
        v.lookAt_y = 0;
        v.lookAt_z = 0;
        v.upDir_x = 0;
        v.upDir_y = 0;
        v.upDir_z = 1;
}


int main( void )
{
	struct Color red     {1, 0, 0};
	struct Color green   {0, 1, 0};
	struct Color yellow  {1, 1, 0};
	struct Color pink    {1, 0, 1};
	struct Color XX      {0, 1, 1};
	struct Color white   {1, 1, 1};
	
	addLightVector(1, 0.5, 0);

	addOrientedRectangleZ(-15, 15, -15, 15, 0, &green);

	addOrientedCuboid(-10, -6, -10, -6, 0, 8, &yellow);
	addOrientedCuboid(-10, -6,   6, 10, 0, 8, &yellow);
	addOrientedCuboid(  6, 10, -10, -6, 0, 8, &yellow);
	addOrientedCuboid(  6, 10,   6, 10, 0, 8, &yellow);

	addOrientedCuboid(  -6,    6, -9.5, -6.5, 0, 3, &yellow);
	addOrientedCuboid(  -6,    6,  6.5,  9.5, 0, 3, &yellow);
	addOrientedCuboid(-9.5, -6.5,   -6,    6, 0, 3, &yellow);
	addOrientedCuboid( 6.5,  9.5,   -6,    6, 0, 3, &yellow);

//	addTriangle(-1, -1, -1,    -1, -1,  1,   1, -1, 1,  &red);
//	addTriangle(-1, -1, -1,     1, -1, -1,   1, -1, 1,  &red);
//	addTriangle(-1,  1, -1,    -1,  1,  1,   1,  1, 1,  &green);
//	addTriangle(-1,  1, -1,     1,  1, -1,   1,  1, 1,  &green);
//
//	addOrientedRectangleX(0, -1, 1, -1, 1, &yellow);
//	addOrientedRectangleY(-1, 1, 0, -1, 1, &pink);
//	addOrientedRectangleZ(-1, 1, -1, 1, 0, &XX);

/*	addLine(-1, 0, -1,   -1, 0,  1, &white);
	addLine(-1, 0,  1,    1, 0,  1, &white);
	addLine( 1, 0,  1,    1, 0, -1, &white);
	addLine( 1, 0, -1,   -1, 0, -1, &white);
*/
	
//	addNormals(&white);

	Gr3dCtx ctx;
	ctx.setGetViewCallback(getView_callback);
	if(!ctx.intGraphics())
		return -1;



	return 0;
}

