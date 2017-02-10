#ifndef __GR3D_CTX__H__
#define __GR3D_CTX__H__

#include <string>
#include <glfw3.h>

class Gr3dView
{
public:
	float camera_x, camera_y, camera_z;
	float lookAt_x, lookAt_y, lookAt_z;
	float upDir_x, upDir_y, upDir_z;
};

class Gr3dCtx
{
public:
	Gr3dCtx();
	bool intGraphics();
	

private:
	// configuable parameters
	std::string window_title;	
        int x_window_size;
        int y_window_size;
        float r_bkg;
        float g_bkg;
        float b_bkg;
	float perspective_angle;
	float perspective_aspectRatio;
	void (*getView_callback)(Gr3dView &);

	// other variables 
	GLFWwindow* window;
	unsigned int VertexArrayID;
	int programID;
	int MatrixID;
	unsigned int vertexbufferId;
	unsigned int colorbufferId;

	// other functions
	void setView(int MatrixID);

};


#endif
