// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>

#define FLOATS_PER_VERTEX 3
#define VORTICES_PER_LINE 2
#define VORTICES_PER_TRIANGLE 3

        static const GLfloat g_vertex_lines[] = { 
		-1, -1, -1,    -1, -1,  1,
		-1,  1, -1,    -1,  1,  1,
		 1,  1, -1,     1,  1,  1,
		 1, -1, -1,     1, -1,  1,

		-1, -1, -1,    -1,  1, -1,
		-1, -1, -1,     1, -1, -1,
		 1,  1, -1,    -1,  1, -1,
		 1,  1, -1,     1, -1, -1,

		-1, -1,  1,    -1,  1,  1,
		-1, -1,  1,     1, -1,  1,
		 1,  1,  1,    -1,  1,  1,
		 1,  1,  1,     1, -1,  1,
        };
	static const float g_vertex_triangles[] = {
		-1, -1, -1,    -1, -1,  1,   1, -1, 1,
		-1, -1, -1,     1, -1, -1,   1, -1, 1,

		-1,  1, -1,    -1,  1,  1,   1,  1, 1,
		-1,  1, -1,     1,  1, -1,   1,  1, 1,
	};
	static const float g_color_triangles[] = {
		1, 0, 0,   1, 0, 0,   1, 0, 0,
		1, 0, 0,   1, 0, 0,   1, 0, 0,
		
		0, 1, 0,   0, 1, 0,   0, 1, 0,
		0, 1, 0,   0, 1, 0,   0, 1, 0,
	};
void processPrimitives(int vertexbufferId, int colorBufferId, const float *vertexBuff, const float *colorBuff, int primitive_count, int vortices_per_primitive, int primitive_type)
{
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
        processPrimitives(vertexbufferId, colorBufferId, g_vertex_triangles, g_color_triangles, 4, VORTICES_PER_TRIANGLE, GL_TRIANGLES);
}



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
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 03 - Matrices", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "SimpleTransform.vertexshader", "SingleColor.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	GLuint vertexbufferId;
	glGenBuffers(1, &vertexbufferId);

	GLuint colorbufferId;
	glGenBuffers(1, &colorbufferId);

	do{
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Use our shader
		glUseProgram(programID);



		setView(MatrixID);
		
//                processLines(vertexbuffer );
                processTriangles(vertexbufferId, colorbufferId );




		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbufferId);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

