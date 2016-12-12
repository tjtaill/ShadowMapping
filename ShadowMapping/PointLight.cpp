#include "stdafx.h"
#include "PointLight.h"
#include "Axis.h"
#include "ColorIndex.h"



PointLight::PointLight( LightNumber lnumber, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	
	float ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
	GLfloat local_view[] = {0.0};

	_color[RED] = r;
	_color[GREEN] = g;
	_color[BLUE] = b;
	_color[ALPHA] = a;

	_number = lnumber;

	// set light colors
	glLightfv(_number, GL_AMBIENT, ambient);
	glLightfv(_number, GL_DIFFUSE, _color);
	//glLightfv(_number, GL_SPECULAR, _color);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR); 
	

}

PointLight::~PointLight(){
	glDisable(_number);

}

GLfloat* PointLight::position(){
	return _position;
}

void PointLight::on(){
	glEnable(GL_LIGHTING);
	glEnable(_number);
}

void PointLight::off(){
	glDisable(_number);
}

void PointLight::draw(){
	glPushMatrix();
		glTranslatef( _position[X], _position[Y], _position[Z] );
		glutSolidSphere( 1.0, 8, 4 );
	glPopMatrix();
}



void PointLight::position_is( const GLfloat* const new_position){
	_position[X] = new_position[X];
	_position[Y] = new_position[Y];
	_position[Z] = new_position[Z];
	_position[W] = 1.0f;
	glLightfv(_number, GL_POSITION, _position);
}

LightNumber PointLight::number(){
	return _number;
}