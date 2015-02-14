#include "primitive.h"

/* boxhdl
 *
 * Generate the geometry and indices required to make a box.
 */
boxhdl::boxhdl(float width, float height, float depth)
{
	/* TODO Assignment 1: Generate the geometry and indices required to make a box.
	 * Calculate its bounding box.
	 */
	 rigid.push_back(rigidhdl());
	 rigid[0].geometry.reserve(8);
	 float length = 0.5*sqrt(width*width+height*height+depth*depth);
	 rigid[0].geometry.push_back(vec8f(0.5*width,0.5*height,0.5*depth,0.5*width/length,0.5*height/length,0.5*depth/length,0.0,0.0));
	 rigid[0].geometry.push_back(vec8f(-0.5*width,0.5*height,0.5*depth,-0.5*width/length,0.5*height/length,0.5*depth/length,0.0,0.0));
	 rigid[0].geometry.push_back(vec8f(-0.5*width,-0.5*height,0.5*depth,-0.5*width/length,-0.5*height/length,0.5*depth/length,0.0,0.0));
	 rigid[0].geometry.push_back(vec8f(0.5*width,-0.5*height,0.5*depth,0.5*width/length,-0.5*height/length,0.5*depth/length,0.0,0.0));
	 rigid[0].geometry.push_back(vec8f(0.5*width,0.5*height,-0.5*depth,0.5*width/length,0.5*height/length,-0.5*depth/length,0.0,0.0));
	 rigid[0].geometry.push_back(vec8f(-0.5*width,0.5*height,-0.5*depth,-0.5*width/length,0.5*height/length,-0.5*depth/length,0.0,0.0));
	 rigid[0].geometry.push_back(vec8f(-0.5*width,-0.5*height,-0.5*depth,-0.5*width/length,-0.5*height/length,-0.5*depth/length,0.0,0.0));
	 rigid[0].geometry.push_back(vec8f(0.5*width,-0.5*height,-0.5*depth,0.5*width/length,-0.5*height/length,-0.5*depth/length,0.0,0.0));
	 
	 //rigid[0].indices.push_back(......)

	 bound = vec6f(-0.5*width,0.5*width,-0.5*height,0.5*height,-0.5*depth,0.5*depth);

}	

boxhdl::~boxhdl()
{

}

/* spherehdl
 *
 * Generate the geometry and indices required to make a sphere.
 */
spherehdl::spherehdl(float radius, int levels, int slices)
{
	rigid.push_back(rigidhdl());

	rigid[0].geometry.reserve(2 + (levels-1)*slices);
	rigid[0].geometry.push_back(vec8f(0.0, 0.0, radius, 0.0, 0.0, 1.0, 0.0, 0.0));
	for (int i = 1; i < levels; i++)
		for (int j = 0; j < slices; j++)
		{
			vec3f dir(sin(m_pi*(float)i/(float)levels)*cos(2.0*m_pi*(float)j/(float)slices),
					  sin(m_pi*(float)i/(float)levels)*sin(2.0*m_pi*(float)j/(float)slices),
					  cos(m_pi*(float)i/(float)levels));
			rigid[0].geometry.push_back(vec8f(radius*dir[0], radius*dir[1], radius*dir[2],
									 dir[0], dir[1], dir[2], 0.0, 0.0));
		}
	rigid[0].geometry.push_back(vec8f(0.0, 0.0, -radius, 0.0, 0.0, -1.0, 0.0, 0.0));

	for (int i = 0; i < slices; i++)
	{
		rigid[0].indices.push_back(1 + (i+1)%slices);
		rigid[0].indices.push_back(1 + i);
		rigid[0].indices.push_back(0);
	}

	for (int i = 0; i < levels-2; i++)
		for (int j = 0; j < slices; j++)
		{
			rigid[0].indices.push_back(1 + i*slices + j);
			rigid[0].indices.push_back(1 + i*slices + (j+1)%slices);
			rigid[0].indices.push_back(1 + (i+1)*slices + j);

			rigid[0].indices.push_back(1 + (i+1)*slices + j);
			rigid[0].indices.push_back(1 + i*slices + (j+1)%slices);
			rigid[0].indices.push_back(1 + (i+1)*slices + (j+1)%slices);
		}

	for (int i = 0; i < slices; i++)
	{
		rigid[0].indices.push_back(1 + (levels-1)*slices);
		rigid[0].indices.push_back(1 + (levels-2)*slices + i);
		rigid[0].indices.push_back(1 + (levels-2)*slices + (i+1)%slices);
	}

	bound = vec6f(-radius, radius, -radius, radius, -radius, radius);
}

spherehdl::~spherehdl()
{

}

/* cylinderhdl
 *
 * Generate the geometry and indices required to make a cylinder.
 */
cylinderhdl::cylinderhdl(float radius, float height, int slices)
{
	/* TODO Assignment 1: Generate the geometry and indices required to make a cylinder.
	 * Calculate its bounding box.
	 */
	 rigid[0].geometry.reserve(2*slices);
	 float length = sqrt(radius*radius+0.25*height*height);
	 for (int i = 0; i < slices; i++){
	 	rigid[0].geometry.push_back(vec8f(radius*cos(2.0*m_pi*(float)i/(float)slices), 0.5*height, radius*sin(2.0*m_pi*(float)i/(float)slices),
	 	radius*cos(2.0*m_pi*(float)i/(float)slices)/length, 0.5*height/length, radius*sin(2.0*m_pi*(float)i/(float)slices)/length,0.0,0.0));
		rigid[0].geometry.push_back(vec8f(radius*cos(2.0*m_pi*(float)i/(float)slices), 0.5*height, -radius*sin(2.0*m_pi*(float)i/(float)slices),
	 	radius*cos(2.0*m_pi*(float)i/(float)slices)/length, 0.5*height/length, -radius*sin(2.0*m_pi*(float)i/(float)slices)/length,0.0,0.0));
	 }

	 //rigid[0].indices.push_back(......)

	 bound = vec6f(-radius,radius,-0.5*height,0.5*height,-radius,radius);

}

cylinderhdl::~cylinderhdl()
{

}

/* pyramidhdl
 *
 * Generate the geometry and indices required to make a pyramid.
 */
pyramidhdl::pyramidhdl(float radius, float height, int slices)
{
	/* TODO Assignment 1: Generate the geometry and indices required to make a pyramid.
	 * Calculate its bounding box.
	 */
	 rigid[0].geometry.reserve(1+slices);
	 rigid[0].geometry.push_back(vec8f(0.0, height, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0));
	 for (int i = 0; i < slices; i++){
	 	rigid[0].geometry.push_back(vec8f(radius*cos(2.0*m_pi*(float)i/(float)slices), 0.0, radius*sin(2.0*m_pi*(float)i/(float)slices), 
		cos(2.0*m_pi*(float)i/(float)slices), 0.0, sin(2.0*m_pi*(float)i/(float)slices), 0.0, 0.0));
	 }

	 //rigid[0].indices.push_back(......)

	 bound = vec6f(-radius,radius,0,height,-radius,radius);

}

pyramidhdl::~pyramidhdl()
{

}
