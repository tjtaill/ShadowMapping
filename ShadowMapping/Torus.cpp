#include "StdAfx.h"
#include "Torus.h"

Torus::Torus(GLdouble inner_radius, GLdouble outer_radius, GLint sides, GLint rings)
{
	_inner_radius = inner_radius;
	_outer_radius = outer_radius;
	_sides = sides;
	_rings = rings;
}

Torus::~Torus(void)
{
	
}

void Torus::draw(void)
{
	glutSolidTorus( _inner_radius, _outer_radius, _sides, _rings );
}
