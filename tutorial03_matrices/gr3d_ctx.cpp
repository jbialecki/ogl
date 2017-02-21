#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <common/shader.hpp>
#include "gr3d_ctx.h"
#include "gr3d.h"

using namespace std;
using namespace glm;

void getView_defaultCallback(Gr3dView &v)
{
	static float f = 0.0;
	f+= 0.002;
//glm::vec3(3*sin(f), 3*cos(f), 2), // Camera is at (4,3,3), in World Space
//glm::vec3(0,0,0), // and looks at the origin
//glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	v.camera_x = 3*sin(f);
	v.camera_y = 3*cos(f);
	v.camera_z = 2;
	v.lookAt_x = 0;
	v.lookAt_y = 0; 
	v.lookAt_z = 0; 
	v.upDir_x = 0;
	v.upDir_y = 1;
	v.upDir_z = 0;
}
Gr3dCtx::Gr3dCtx()
{
	window_title = "3D graphics";
	x_window_size = 1024;
	y_window_size = 768;
	r_bkg = 0;
	g_bkg = 0;
	b_bkg = 0.4;
	getView_callback = getView_defaultCallback;
}
void Gr3dCtx::setView(int MatrixID)
{
	static Gr3dView v;
	getView_callback(v);
        // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

        // Camera matrix
        glm::mat4 View       = glm::lookAt(
                                                glm::vec3(v.camera_x, v.camera_y, v.camera_z), // Camera is at (4,3,3), in World Space
                                                glm::vec3(v.lookAt_x, v.lookAt_y, v.lookAt_z), // and looks at the origin
                                                glm::vec3(v.upDir_x, v.upDir_y, v.upDir_z)  // Head is up (set to 0,-1,0 to look upside-down)
                                           );
        // Model matrix : an identity matrix (model will be at the origin)
        glm::mat4 Model      = glm::mat4(1.0f);
        // Our ModelViewProjection : multiplication of our 3 matrices
        glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

        // Send our transformation to the currently bound shader, 
        // in the "MVP" uniform
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
}

bool Gr3dCtx::intGraphics()
{
        if( !glfwInit() )
        {
                fprintf( stderr, "Failed to initialize GLFW\n" );
                getchar();
                return false;
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

        // Open a window and create its OpenGL context
        window = glfwCreateWindow(  x_window_size, y_window_size, window_title.c_str(), NULL, NULL);
        if( window == NULL ){
                fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
                getchar();
                glfwTerminate();
                return false;
        }
        glfwMakeContextCurrent(window);

        // Initialize GLEW
        glewExperimental = true; // Needed for core profile
        if (glewInit() != GLEW_OK) {
                fprintf(stderr, "Failed to initialize GLEW\n");
                getchar();
                glfwTerminate();
                return false;
        }

        // Ensure we can capture the escape key being pressed below
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

        // Dark blue background
        glClearColor(r_bkg, g_bkg, b_bkg, 0.0f);

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);

        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        // Create and compile our GLSL program from the shaders
        programID = LoadShaders( "SimpleTransform.vertexshader", "SingleColor.fragmentshader" );
        // Get a handle for our "MVP" uniform
        MatrixID = glGetUniformLocation(programID, "MVP");

        glGenBuffers(1, &linesVertexBuffId);
        glGenBuffers(1, &linesColorBuffId);
        glGenBuffers(1, &trianglesVertexBuffId);
        glGenBuffers(1, &trianglesColorBuffId);

	triangles2vertexes();
	lines2vertexes();

        do{
                // Clear the screen
                glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


                // Use our shader
                glUseProgram(programID);



                setView(MatrixID);

                processLines(linesVertexBuffId, linesColorBuffId );
                processTriangles(trianglesVertexBuffId, trianglesColorBuffId );




                // Swap buffers
                glfwSwapBuffers(window);
                glfwPollEvents();

        } // Check if the ESC key was pressed or the window was closed
        while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
                   glfwWindowShouldClose(window) == 0 );

        // Cleanup VBO and shader
        glDeleteBuffers(1, &linesVertexBuffId);
        glDeleteBuffers(1, &linesColorBuffId);
        glDeleteBuffers(1, &trianglesVertexBuffId);
        glDeleteBuffers(1, &trianglesColorBuffId);
        glDeleteProgram(programID);
        glDeleteVertexArrays(1, &VertexArrayID);

        // Close OpenGL window and terminate GLFW
        glfwTerminate();
	
	return true;
}
