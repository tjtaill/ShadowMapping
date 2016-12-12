#include "StdAfx.h"

#include "SpotLight.h"

#include "ColorIndex.h"
#include "Axis.h"




SpotLight::SpotLight(
			LightNumber lightNumber,
			GLfloat red, 
			GLfloat green,
			GLfloat blue,
			GLdouble bottomRadius,
			GLdouble topRadius,
			GLdouble height,
			GLuint slices,
			GLuint stacks, 
			GLfloat spotCutoff,
			GLfloat spotExponent)
{
	_lightNumber = lightNumber;
	_color[RED] = red;
	_color[GREEN] = green;
	_color[BLUE] = blue;
	_color[ALPHA] = 1.0f;
	_bottomRadius = bottomRadius;
	_topRadius = topRadius;
	_height = height;
	_slices = slices;
	_stacks = stacks;
	_spotCutoff = spotCutoff;
	_spotExponent = spotExponent;
	_quadric = gluNewQuadric();
	glLightf( _lightNumber, GL_SPOT_CUTOFF, _spotCutoff );
	glLightf( _lightNumber, GL_SPOT_EXPONENT, _spotExponent );
	glLightfv( _lightNumber, GL_DIFFUSE, _color );
	glLightfv( _lightNumber, GL_SPECULAR, _color );
	//glLightf( _lightNumber, GL_CONSTANT_ATTENUATION, 2.0f );
	//glLightf( _lightNumber, GL_LINEAR_ATTENUATION, 0.5f );
	//glLightf( _lightNumber, GL_QUADRATIC_ATTENUATION, 0.2f );

	
}

SpotLight::~SpotLight(void)
{
	gluDeleteQuadric( _quadric );
}

void SpotLight::on(){
	glEnable(GL_LIGHTING);
	glEnable( _lightNumber );
}

void SpotLight::off(){
	glDisable( _lightNumber );
}

void SpotLight::position_is(GLfloat xpos, GLfloat ypos, GLfloat zpos){
	_position[X] = xpos;
	_position[Y] = ypos;
	_position[Z] = zpos;
	_position[W] = 1.0f;
	glLightfv(_lightNumber, GL_POSITION, _position);
	
}

// don't call this use rotation instead
void SpotLight::direction_is(GLfloat xdir, GLfloat ydir, GLfloat zdir){
	_direction[X] = xdir;
	_direction[Y] = ydir;
	_direction[Z] = zdir;
	_direction[W] = 1.0f;
	glLightfv(_lightNumber, GL_SPOT_DIRECTION, _direction);

}

void SpotLight::draw(){
	gluCylinder( _quadric, _bottomRadius, _topRadius, _height, _slices, _stacks );	
}

