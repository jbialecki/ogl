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
#include "constructed2.h"


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
	
	addLightVector(1, -0.5, 0);
	addLine(0, 0, 0, 20, 0, 0, &white);

	//addOrientedRectangleZ(-15, 15, -15, 15, 0, &green);
//	Polygon grass = mkRectangleZ(-15, 15, -15, 15, 0);
//	grass.render(green);
	
	Polyhedron tower = mkCuboid(4, 4, 8).adjust(Axis::Z, Adjust::MIN, 0);
	tower.translate(Vector(-8, -8, 0)).render(XX);
	tower.translate(Vector(-8,  8, 0)).render(XX);
	tower.translate(Vector( 8, -8, 0)).render(XX);
	tower.translate(Vector( 8,  8, 0)).render(XX);

	Polyhedron wall = mkCuboid(12, 3, 3).adjust(Axis::Z, Adjust::MIN, 0);
	wall.translate(Vector(0,  8, 0)).render(pink);
	wall.translate(Vector(0, -8, 0)).render(pink);
	wall.rotateZ(Pi/2).translate(Vector( 8, 0, 0)).render(pink);
	wall.rotateZ(Pi/2).translate(Vector(-8, 0, 0)).render(pink);

	Polyhedron wallRoof = mkPrism(mkIsoscelesTriangle(4, 3, Plane::XZ), Vector(0, 12, 0)).adjust(Axis::Y, Adjust::CENTER, 0).adjust(Axis::Z, Adjust::MIN, 3);//translate(Vector(0, 6, 3));
	wallRoof.translate(Vector( 8, 0, 0)).render(yellow);
	wallRoof.translate(Vector(-8, 0, 0)).render(yellow);
	wallRoof.rotateZ(Pi/2).translate(Vector(0, -8, 0)).render(yellow);
	wallRoof.rotateZ(Pi/2).translate(Vector(0,  8, 0)).render(yellow);
	
	addNormals(&white);

	Gr3dCtx ctx;
	ctx.setGetViewCallback(getView_callback);
	if(!ctx.intGraphics())
		return -1;



	return 0;
}

