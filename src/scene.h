#include "canvas.h"

#ifndef scene_h
#define scene_h

struct objecthdl;
struct camerahdl;

struct scenehdl
{
	scenehdl();
	~scenehdl();

	vector<objecthdl*> objects;
	vector<camerahdl*> cameras;
	canvashdl *canvas;

	int active_camera;
	int active_object;

	// Whether and how to render the normals
	enum
	{
		none = 0,
		face = 1,
		vertex = 2
	} render_normals;

	// Whether or not to render the lights or the cameras or both
	bool render_cameras;

	void draw();

	bool active_camera_valid();
	bool active_object_valid();

	void create_camera();

};

#endif
