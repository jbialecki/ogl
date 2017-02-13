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




int main( void )
{
	struct Color red {1, 0, 0};
	struct Color green {0, 1, 0};
	addTriangle(-1, -1, -1,    -1, -1,  1,   1, -1, 1,  &red);
	addTriangle(-1, -1, -1,     1, -1, -1,   1, -1, 1,  &red);
	addTriangle(-1,  1, -1,    -1,  1,  1,   1,  1, 1,  &green);
	addTriangle(-1,  1, -1,     1,  1, -1,   1,  1, 1,  &green);

	Gr3dCtx ctx;
	if(!ctx.intGraphics())
		return -1;



	return 0;
}

