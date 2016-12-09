// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <common/shader.hpp>


#define FLOATS_PER_VERTEX 3
#define VORTICES_PER_LINE 2
#define VORTICES_PER_TRIANGLE 3

	static const GLfloat g_vertex_lines[] = { 
		 0.6f,  0.6f, 0.0f,
		 0.7f,  0.7f, 0.0f,

		 0.8f,  0.8f, 0.0f,
		 0.9f,  0.9f, 0.0f,
	};
	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,

		 0.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		-1.0f,  0.0f, 0.0f,
	};

void processPrimitives(GLuint vertexbuffer, const GLfloat *buff, int primitive_count, int vortices_per_primitive, int primitive_type)
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(	
			GL_ARRAY_BUFFER, 
			primitive_count * vortices_per_primitive * FLOATS_PER_VERTEX * sizeof(float), 
			buff, 
			GL_STATIC_DRAW
		);
	glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			FLOATS_PER_VERTEX,  // floats per vertex
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

	glDrawArrays(	
			primitive_type, 
			0, 	  					// idx of first vertex in buffer
			primitive_count * vortices_per_primitive	// number of vortices
		);  
	glDisableVertexAttribArray(0);
}
void processLines(unsigned int vertexbuffer )
{
	processPrimitives(vertexbuffer, g_vertex_lines, 2, VORTICES_PER_LINE, GL_LINES);
}

void processTriangles(unsigned int vertexbuffer)
{
	processPrimitives(vertexbuffer, g_vertex_buffer_data, 2, VORTICES_PER_TRIANGLE, GL_TRIANGLES);
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
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);
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

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );



	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);

	do{

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		// Use our shader
		glUseProgram(programID);

		processLines(vertexbuffer );
		processTriangles(vertexbuffer );


		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

