#include "stdafx.h"
#include <algorithm>
#include "DirectionalLight.h"
#include "Axis.h"
#include "ColorIndex.h"

using namespace std;

DirectionalLight::DirectionalLight( LightNumber lnumber, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	float ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
	GLfloat local_view[] = {0.0};

	_position[X] = 0.0f;
	_position[Y] = 0.0f;
	_position[Z] = 0.0f;
	_position[W] = 0.0f;

	_color[RED] = r;
	_color[GREEN] = g;
	_color[BLUE] = b;
	_color[ALPHA] = a;

	_number = lnumber;

	// set light colors
	glLightfv(_number, GL_AMBIENT, ambient);
	glLightfv(_number, GL_DIFFUSE, _color);
	glLightfv(_number, GL_SPECULAR, _color);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR); 
	

}

DirectionalLight::~DirectionalLight(){
	glDisable(_number);

}

GLfloat* DirectionalLight::position(){
	return _position;
}

void DirectionalLight::on(){
	glEnable(GL_LIGHTING);
	glEnable(_number);
}

void DirectionalLight::off(){
	glDisable(_number);
}

void DirectionalLight::draw(){
	//GLdouble old_color[4];
	//glGetDoublev( GL_CURRENT_COLOR, old_color );
	//glColor4fv( _color );
	glPushMatrix();
		glTranslatef( _position[X], _position[Y], _position[Z] );
		glutSolidSphere( 1.0, 8, 4 );
	glPopMatrix();
	//glColor4dv( old_color );
}



void DirectionalLight::position_is( const GLfloat* const new_position ){
	copy( &new_position[X], &new_position[Z], &_position[X] );
	_position[W] = 0.0f;
	glLightfv(_number, GL_POSITION, _position);

}

LightNumber DirectionalLight::number(){
	return _number;
}