#include "opengl.h"
#include "standard.h"
#include "canvas.h"
#include "scene.h"
#include "camera.h"
#include "model.h"
#include "primitive.h"
#include "tinyfiledialogs.h"

using namespace std;

int window_id;

canvashdl canvas(750, 750);
scenehdl scene;

int mousex = 0, mousey = 0;
bool bound = false;
bool menu = false;

enum menu_type{
	Ojects = 0, Cameras = 1, Polygon = 2, Culling = 3, Normals = 4, Quit = 5
};

enum object_type{
	Box = 0, Cylinder = 1, Sphere = 2, Pyramid = 3, Model = 4
};

enum camera_type{
	Fovy = 0,
	Aspect = 1, 
	Width = 2, 
	Height = 3, 
	Near = 4, 
	Far = 5, 
	Toggle_Draw = 6, 
	Clear_Focus = 7, 
	Ortho = 8, 
	Frustum = 9, 
	Perspective = 10
};

enum polygon_type{
	Point = 0, Line = 1
};

enum culling_type{
	None_c = -1, Front = 0, Back = 1
};

enum normal_type{
	None_n = -1, Face = 0, Vertex = 1
};

namespace manipulate
{
	enum type
	{
		none = -1,
		translate = 0,
		rotate = 1,
		scale = 2,
		fovy = 3,
		aspect = 4,
		width = 5,
		height = 6,
		front = 7,
		back = 8
	};
}







manipulate::type manipulator;

bool keys[256];

void init(string working_directory)
{
	for (int i = 0; i < 256; i++)
		keys[i] = false;

    canvas.working_directory = working_directory;
	scene.canvas = &canvas;
	// TODO Assignment 1: Initialize the Scene as necessary.


	scene.active_camera = 0;
	scene.active_object = 0;
	boxhdl *box = new boxhdl(10.0,10.0,10.0);
	scene.objects.push_back(box);

	orthohdl *ort = new orthohdl();
	scene.cameras.push_back(ort);


	
}

void displayfunc()
{
	canvas.clear_color_buffer();

	scene.draw();

	canvas.swap_buffers();
}

void reshapefunc(int w, int h)
{
	canvas.viewport(w, h);
	glutPostRedisplay();
}

void pmotionfunc(int x, int y)
{
	if (bound)
	{
		int deltax = x - mousex;
		int deltay = y - mousey;

		mousex = x;
		mousey = y;

		bool warp = false;
		if (mousex > 3*canvas.get_width()/4 || mousex < canvas.get_width()/4)
		{
			mousex = canvas.get_width()/2;
			warp = true;
		}

		if (mousey > 3*canvas.get_height()/4 || mousey < canvas.get_height()/4)
		{
			mousey = canvas.get_height()/2;
			warp = true;
		}

		if (warp)
			glutWarpPointer(mousex, mousey);

		// TODO Assignment 1: Use the mouse delta to change the orientation of the active camera

		glutPostRedisplay();
	}
	else if (scene.active_camera_valid())
	{
		/* TODO Assignment 1: Figure out which object the mouse pointer is hovering over and make
		 * that the active object.
		 */
	}
}

void mousefunc(int button, int state, int x, int y)
{
	mousex = x;
	mousey = y;
}

void motionfunc(int x, int y)
{
	if (!bound && !menu)
	{
		int deltax = x - mousex;
		int deltay = mousey - y;

		mousex = x;
		mousey = y;

		/* TODO Assignment 1: Implement the functionality for the following operations here:
		 * translation, rotation, and scaling of an object
		 * changing the fovy, aspect, width, height, near, or far values of the active camera
		 *
		 * This uses the mouse, so you'll have to determine the world coordinate position of the
		 * mouse pointer.
		 */
		glutPostRedisplay();
	}
	else if (!bound)
	{
		menu = false;
		pmotionfunc(x, y);
	}
}

void keydownfunc(unsigned char key, int x, int y)
{
	keys[key] = true;

	if (key == 27) // Escape Key Pressed
	{
		glutDestroyWindow(window_id);
		exit(0);
	}
	else if (key == 'm' && bound)
	{
		bound = false;
		glutSetCursor(GLUT_CURSOR_INHERIT);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
	}
	else if (key == 'm' && !bound)
	{
		bound = true;
		glutSetCursor(GLUT_CURSOR_NONE);
		glutDetachMenu(GLUT_RIGHT_BUTTON);
		mousex = x;
		mousey = y;
	}
}

void keyupfunc(unsigned char key, int x, int y)
{
	keys[key] = false;
}

void idlefunc()
{
	bool change = false;

	// TODO Assignment 1: handle continuous keyboard inputs

	if (change)
		glutPostRedisplay();
}

void menustatusfunc(int status, int x, int y)
{
	if (status == GLUT_MENU_IN_USE)
		menu = true;
}

void processMenuEvents(int id){
	switch(id){
		case 0:
		;
		case 1:
		;
		case 2:
		;
		case 3:
		;
		case 4:
		;
		case 5:
		exit(1);
	}
};

void processObjectEvents(int id){
	switch(id){
		case 0:
		;
		case 1:
		;
		case 2:
		;
		case 3:
		;
		case 4:
		;
	}
}

void processCameraEvents(int id){
	switch(id){
		case 0:
		;
		case 1:
		;
		case 2:
		;
		case 3:
		;
		case 4:
		;
		case 5:
		;
		case 6:
		;
		case 7:
		;
		case 8:
		;
		case 9:
		;
		case 10:
		;
	}
}

void processPolygonEvents(int id){
	switch(id){
		case 0:
		;
		case 1:
		;
	}
}

void processCullingEvents(int id){
	switch(id){
		case 0:
		;
		case 1:
		;
		case 2:
		;
	}
}

void processNormalEvents(int id){
	switch(id){
		case 0:
		;
		case 1:
		;
		case 2:
		;
	}
}

void create_menu()
{
	/* TODO Assignment 1: Implement a menu that allows the following operations:
	 * - create a box, cylinder, sphere, pyramid, or load a model
	 * - change the fovy, aspect, width, height, near or far values of the active camera
	 * - enable/disable drawing of cameras
	 * - create an orthographic, frustum, or perspective camera
	 * - set the polygon mode to point or line
	 * - enable culling for front or back face or disable culling
	 * - enable rendering of vertex or face normals, or disabe both
	 * - Set an object or camera as the focus of the active camera (using canvashdl::look_at)
	 * - Unset the focus of the active camera
	 * - Translate, rotate, or scale an object or camera
	 * - delete an object or camera
	 * - Set the active camera
	 * - quit
	 */

	int Menu, Objects, Cameras, Polygon, Culling, Normals, Quit;
	
	Objects = glutCreateMenu(processObjectEvents);
	glutAddMenuEntry("Box",Box);
	glutAddMenuEntry("Cylinder",Cylinder);
	glutAddMenuEntry("Sphere",Sphere);
	glutAddMenuEntry("Pyramid",Pyramid);
	glutAddMenuEntry("Model",Model);

	Cameras = glutCreateMenu(processCameraEvents);
	glutAddMenuEntry("Fovy",Fovy);
	glutAddMenuEntry("Aspect",Aspect);
	glutAddMenuEntry("Width",Width);
	glutAddMenuEntry("Height",Height);
	glutAddMenuEntry("Near",Near);
	glutAddMenuEntry("Far",Far);
	glutAddMenuEntry("Toggle Draw",Toggle_Draw);
	glutAddMenuEntry("Clear Focus",Clear_Focus);
	glutAddMenuEntry("Ortho",Ortho);
	glutAddMenuEntry("Frustum",Frustum);
	glutAddMenuEntry("Perspective",Perspective);

	Polygon = glutCreateMenu(processPolygonEvents);
	glutAddMenuEntry("Point",Point);
	glutAddMenuEntry("Line",Line);

	Culling = glutCreateMenu(processCullingEvents);
	glutAddMenuEntry("None",None_c);
	glutAddMenuEntry("Front",Front);
	glutAddMenuEntry("Back",Back);

	Normals = glutCreateMenu(processNormalEvents);
	glutAddMenuEntry("None",None_n);
	glutAddMenuEntry("Face",Face);
	glutAddMenuEntry("Vertex",Vertex);


	Menu = glutCreateMenu(processMenuEvents);
	glutAddSubMenu("Objects",Objects);
	glutAddSubMenu("Cameras",Cameras);
	glutAddSubMenu("Polygon",Polygon);
	glutAddSubMenu("Culling",Culling);
	glutAddSubMenu("Normals",Normals);
	glutAddMenuEntry("Quit",Quit);


	/* TODO Assignment 2: Add to the menu the following operations:
	 * - create directional, point, or spot lights
	 * - enable/disable rendering of lights
	 * - set the polygon mode to fill
	 * - change the ambient, diffuse, or specular color of a light
	 * - change the attenuation parameters of a point or spot light
	 * - set the shading mode to none, flat, gouraud, or phong
	 */

	glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMenuStatusFunc(menustatusfunc);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
    int display_mode = GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE;
#ifdef OSX_CORE3
    display_mode |= GLUT_3_2_CORE_PROFILE;
#endif
	glutInitDisplayMode(display_mode);
	
	glutInitWindowSize(750, 750);
	glutInitWindowPosition(0, 0);
	window_id = glutCreateWindow("Assignment");

#ifdef __GLEW_H__
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		cerr << "Error: " << glewGetErrorString(err) << endl;
		exit(1);
	}
	cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << endl;
#endif
    
	cout << "Status: Using OpenGL " << glGetString(GL_VERSION) << endl;
	cout << "Status: Using GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

    
    init(string(argv[0]).substr(0, string(argv[0]).find_last_of("/\\")) + "/");
	create_menu();

	glutReshapeFunc(reshapefunc);
	glutDisplayFunc(displayfunc);
	glutIdleFunc(idlefunc);

	glutPassiveMotionFunc(pmotionfunc);
	glutMotionFunc(motionfunc);
	glutMouseFunc(mousefunc);

	glutKeyboardFunc(keydownfunc);
	glutKeyboardUpFunc(keyupfunc);

	glutMainLoop();
}
