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




void setView(int MatrixID)
{
static float f = 0.0;
f+= 0.01;

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	// Camera matrix
	glm::mat4 View       = glm::lookAt(
						glm::vec3(3*sin(f), 3*cos(f), 2), // Camera is at (4,3,3), in World Space
						glm::vec3(0,0,0), // and looks at the origin
						glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
					   );
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
}


int main( void )
{
	addTriangle(-1, -1, -1,    -1, -1,  1,   1, -1, 1,  1, 0, 0,   1, 0, 0,   1, 0, 0);
	addTriangle(-1, -1, -1,     1, -1, -1,   1, -1, 1,  1, 0, 0,   1, 0, 0,   1, 0, 0);
	addTriangle(-1,  1, -1,    -1,  1,  1,   1,  1, 1,  0, 1, 0,   0, 1, 0,   0, 1, 0);
	addTriangle(-1,  1, -1,     1,  1, -1,   1,  1, 1,  0, 1, 0,   0, 1, 0,   0, 1, 0);

	Gr3dCtx ctx;
	if(!ctx.intGraphics())
		return -1;



	return 0;
}

