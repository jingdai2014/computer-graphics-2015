#include "canvas.h"
#include "core/geometry.h"

canvashdl::canvashdl(int w, int h)
{
	width = w;
	height = h;
	last_reshape_time = -1.0;
	reshape_width = w;
	reshape_height = h;
	initialized = false;

	color_buffer = new unsigned char[width*height*3];
	// TODO Assignment 2: Initialize the depth buffer

	screen_texture = 0;
	screen_geometry = 0;
	screen_shader = 0;

	active_matrix = modelview_matrix;

	for (int i = 0; i < 3; i++)
		matrices[i] = identity<float, 4, 4>();

	polygon_mode = line;
	culling = backface;
}

canvashdl::~canvashdl()
{
	if (color_buffer != NULL)
	{
		delete [] color_buffer;
		color_buffer = NULL;
	}

	// TODO Assignment 2: Clean up the depth buffer
}

void canvashdl::clear_color_buffer()
{
	memset(color_buffer, 0, width*height*3*sizeof(unsigned char));
}

void canvashdl::clear_depth_buffer()
{
	// TODO Assignment 2: Clear the depth buffer
}

void canvashdl::resize(int w, int h)
{
	// TODO Assignment 2: resize the depth buffer

	last_reshape_time = -1.0;

	if (color_buffer != NULL)
	{
		delete [] color_buffer;
		color_buffer = NULL;
	}

	width = w;
	height = h;

	color_buffer = new unsigned char[w*h*3];

	glActiveTexture(GL_TEXTURE0);
	check_error(__FILE__, __LINE__);
	glBindTexture(GL_TEXTURE_2D, screen_texture);
	check_error(__FILE__, __LINE__);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, color_buffer);
	check_error(__FILE__, __LINE__);
}

/* set_matrix
 *
 * Change which matrix is active.
 */
void canvashdl::set_matrix(matrix_id matid)
{
	// TODO Assignment 1: Change which matrix is active.
}

/* load_identity
 *
 * Set the active matrix to the identity matrix.
 */
void canvashdl::load_identity()
{
	// TODO Assignment 1: Set the active matrix to the identity matrix.
}

/* rotate
 *
 * Multiply the active matrix by a rotation matrix.
 */
void canvashdl::rotate(float angle, vec3f axis)
{
	// TODO Assignment 1: Multiply the active matrix by a rotation matrix.
}

/* translate
 *
 * Multiply the active matrix by a translation matrix.
 */
void canvashdl::translate(vec3f direction)
{
	// TODO Assignment 1: Multiply the active matrix by a translation matrix.
}

/* scale
 *
 * Multiply the active matrix by a scaling matrix.
 */
void canvashdl::scale(vec3f size)
{
	// TODO Assignment 1: Multiply the active matrix by a scaling matrix.
}

/* perspective
 *
 * Multiply the active matrix by a perspective projection matrix.
 */
void canvashdl::perspective(float fovy, float aspect, float n, float f)
{
	// TODO Assignment 1: Multiply the active matrix by a perspective projection matrix.
}

/* frustum
 *
 * Multiply the active matrix by a frustum projection matrix.
 */
void canvashdl::frustum(float l, float r, float b, float t, float n, float f)
{
	// TODO Assignment 1: Multiply the active matrix by a frustum projection matrix.
}

/* ortho
 *
 * Multiply the active matrix by an orthographic projection matrix.
 */
void canvashdl::ortho(float l, float r, float b, float t, float n, float f)
{
	// TODO Assignment 1: Multiply the active matrix by an orthographic projection matrix.
}

void canvashdl::look_at(vec3f eye, vec3f at, vec3f up)
{
	// TODO Assignment 1: Emulate the functionality of gluLookAt
}

/* to_window
 *
 * Pixel coordinates to window coordinates.
 */
vec3f canvashdl::to_window(vec2i pixel)
{
	/* TODO Assignment 1: Given a pixel coordinate (x from 0 to width and y from 0 to height),
	 * convert it into window coordinates (x from -1 to 1 and y from -1 to 1).
	 */
	return vec3f();
}

/* unproject
 *
 * Unproject a window coordinate into world coordinates.
 */
vec3f canvashdl::unproject(vec3f window)
{
	// TODO Assignment 1: Unproject a window coordinate into world coordinates.
	return vec3f();
}

/* shade_vertex
 *
 * This is the vertex shader.
 */
vec8f canvashdl::shade_vertex(vec8f v)
{
	// TODO Assignment 1: Do all of the necessary transformations (normal, projection, modelview, etc)

	// TODO Assignment 2: Implement Flat and Gouraud shading.
	//return vec8f();
	return v;
}

/* shade_fragment
 *
 * This is the fragment shader. The pixel color is determined here.
 */
vec3f canvashdl::shade_fragment(vec8f v)
{
	// TODO Assignment 1: Pick a color, any color (as long as it is distinguishable from the background color).

	/* TODO Assignment 2: Figure out the pixel color due to lighting and materials
	 * and implement phong shading.
	 */
	return vec3f(255,255,255);
}

/* plot
 *
 * Plot a pixel.
 */
void canvashdl::plot(vec2i xy, vec8f v)
{
	// TODO Assignment 1: Plot a pixel, calling the fragment shader.
	//cout<<"canvas_plot"<<endl;
	vec3f color = shade_fragment(v);
/////////////////to_window//////////////////////////
	color_buffer[(int)((xy[1]+0.5*height)*width+xy[0]+0.5*width)*3] = color[0];
	color_buffer[(int)((xy[1]+0.5*height)*width+xy[0]+0.5*width)*3+1] = color[1];
	color_buffer[(int)((xy[1]+0.5*height)*width+xy[0]+0.5*width)*3+2] = color[2];

	// TODO Assignment 2: Check the pixel depth against the depth buffer.
}

/* plot_point
 *
 * Plot a point given in window coordinates.
 */
void canvashdl::plot_point(vec8f v)
{
	// TODO Assignment 1: Plot a point given in window coordinates.
	//cout<<"canvas_plotpoint"<<endl;
	vec2i u = vec2i((int)v[0],(int)v[1]);
	plot(u,v);
}

/* plot_line
 *
 * Plot a line defined by two points in window coordinates.
 */
void canvashdl::plot_line(vec8f v1, vec8f v2)
{
	// TODO Assignment 1: Implement Bresenham's Algorithm.

	// TODO Assignment 2: Add interpolation for the normals and texture coordinates as well.
}

/* plot_half_triangle
 *
 * Plot half of a triangle defined by three points in window coordinates (v1, v2, v3).
 * The remaining inputs are as follows (s1, s2, s3) are the pixel coordinates of (v1, v2, v3),
 * and (ave) is the average value of the normal and texture coordinates for flat shading.
 */
void canvashdl::plot_half_triangle(vec2i s1, vec2i s2, vec2i s3, vec8f v1, vec8f v2, vec8f v3, vec5f ave)
{
	/* TODO Assignment 2: Implement Bresenham's algorithm. You may plot the horizontal
	 * half or the vertical half. Add interpolation for the normals and texture coordinates as well.
	 */
}

/* plot_triangle
 *
 * Plot a triangle. (v1, v2, v3) are given in window coordinates.
 */
void canvashdl::plot_triangle(vec8f v1, vec8f v2, vec8f v3)
{
	/* TODO Assignment 1: Use the above functions to plot a whole triangle. Don't forget to
	 * take into account the polygon mode. You should be able to render the
	 * triangle as 3 points or 3 lines.
	 */

	// TODO Assignment 2: Add in the fill polygon mode.
}

/* draw_points
 *
 * Draw a set of 3D points on the canvas. Each point in geometry is
 * formatted (vx, vy, vz, nx, ny, nz, s, t).
 */
void canvashdl::draw_points(const vector<vec8f> &geometry)
{
	// TODO Assignment 1: Clip the points against the frustum, call the vertex shader, and then draw them.
	//cout<<"canvas_draw"<<endl;
	for(int i=0; i<geometry.size(); i++){
		plot_point(geometry[i]);
	}
	//out<<"canvas_draw_end"<<endl;
}

/* Draw a set of 3D lines on the canvas. Each point in geometry
 * is formatted (vx, vy, vz, nx, ny, nz, s, t).
 */
void canvashdl::draw_lines(const vector<vec8f> &geometry, const vector<int> &indices)
{
	// TODO Assignment 1: Clip the lines against the frustum, call the vertex shader, and then draw them.
}

/* Draw a set of 3D triangles on the canvas. Each point in geometry is
 * formatted (vx, vy, vz, nx, ny, nz, s, t). Don't forget to clip the
 * triangles against the clipping planes of the projection. You can't
 * just not render them because you'll get some weird popping at the
 * edge of the view. Also, this is where font/back face culling is implemented.
 */
void canvashdl::draw_triangles(const vector<vec8f> &geometry, const vector<int> &indices)
{
	/* TODO Assignment 1: Clip the triangles against the frustum, call the vertex shader,
	 * break the resulting polygons back into triangles, implement front and back face
	 * culling, and then draw the remaining triangles.
	 */
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Do not edit anything below here, that code just sets up OpenGL to render a single
 * quad that covers the whole screen, applies the color_buffer as a texture to it, and
 * keeps the buffer size and texture up to date.
 */
void canvashdl::load_texture()
{
	glGenTextures(1, &screen_texture);
	check_error(__FILE__, __LINE__);
	glActiveTexture(GL_TEXTURE0);
	check_error(__FILE__, __LINE__);
	glBindTexture(GL_TEXTURE_2D, screen_texture);
	check_error(__FILE__, __LINE__);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	check_error(__FILE__, __LINE__);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	check_error(__FILE__, __LINE__);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	check_error(__FILE__, __LINE__);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	check_error(__FILE__, __LINE__);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	check_error(__FILE__, __LINE__);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, color_buffer);
	check_error(__FILE__, __LINE__);
}

void canvashdl::load_geometry()
{
	// x, y, s, t
	const GLfloat geometry[] = {
			-1.0, -1.0, 0.0, 0.0,
			 1.0, -1.0, 1.0, 0.0,
			-1.0,  1.0, 0.0, 1.0,
			-1.0,  1.0, 0.0, 1.0,
			 1.0, -1.0, 1.0, 0.0,
			 1.0,  1.0, 1.0, 1.0
	};

	glGenBuffers(1, &screen_geometry);
	glBindBuffer(GL_ARRAY_BUFFER, screen_geometry);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*4*6, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*4*6, geometry);
}

void canvashdl::load_shader()
{
	GLuint vertex = load_shader_file(working_directory + "res/canvas.vx", GL_VERTEX_SHADER);
	GLuint fragment = load_shader_file(working_directory + "res/canvas.ft", GL_FRAGMENT_SHADER);

	screen_shader = glCreateProgram();
	glAttachShader(screen_shader, vertex);
	glAttachShader(screen_shader, fragment);
	glLinkProgram(screen_shader);
}

void canvashdl::init_opengl()
{
	glEnable(GL_TEXTURE_2D);
	glViewport(0, 0, width, height);

	load_texture();
	load_geometry();
	load_shader();
	initialized = true;
}

void canvashdl::check_error(const char *file, int line)
{
	GLenum error_code;
	error_code = glGetError();
	if (error_code != GL_NO_ERROR)
		cerr << "error: " << file << ":" << line << ": " << gluErrorString(error_code) << endl;
}

double canvashdl::get_time()
{
	timeval gtime;
	gettimeofday(&gtime, NULL);
	return gtime.tv_sec + gtime.tv_usec*1.0E-6;
}

void canvashdl::viewport(int w, int h)
{
	glViewport(0, 0, w, h);
	last_reshape_time = get_time();
	reshape_width = w;
	reshape_height = h;
}

void canvashdl::swap_buffers()
{

	if (!initialized)
		init_opengl();

	if (last_reshape_time > 0.0 && get_time() - last_reshape_time > 0.125)
		resize(reshape_width, reshape_height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(screen_shader);
	check_error(__FILE__, __LINE__);

	glActiveTexture(GL_TEXTURE0);
	check_error(__FILE__, __LINE__);
	glBindTexture(GL_TEXTURE_2D, screen_texture);
	check_error(__FILE__, __LINE__);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, color_buffer);
	check_error(__FILE__, __LINE__);
	glUniform1i(glGetUniformLocation(screen_shader, "tex"), 0);
	check_error(__FILE__, __LINE__);

	glBindBuffer(GL_ARRAY_BUFFER, screen_geometry);
	check_error(__FILE__, __LINE__);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	check_error(__FILE__, __LINE__);
	glEnableClientState(GL_VERTEX_ARRAY);
	check_error(__FILE__, __LINE__);

	glTexCoordPointer(2, GL_FLOAT, sizeof(GLfloat)*4, (float*)(sizeof(GLfloat)*2));
	check_error(__FILE__, __LINE__);
	glVertexPointer(2, GL_FLOAT, sizeof(GLfloat)*4, NULL);
	check_error(__FILE__, __LINE__);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	check_error(__FILE__, __LINE__);

	glDisableClientState(GL_VERTEX_ARRAY);
	check_error(__FILE__, __LINE__);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	check_error(__FILE__, __LINE__);

	glutSwapBuffers();
	check_error(__FILE__, __LINE__);
}

int canvashdl::get_width()
{
	return width;
}

int canvashdl::get_height()
{
	return height;
}
