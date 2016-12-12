#ifndef POINT_LIGHT_DOT_H
#define POINT_LIGHT_DOT_H

/**
  *@file Light.h
  *@author Troy Taillefer
  *@version 0.1
  *@date January 30, 2008
  *
  */
#include "LightNumber.h"






/**
  *@class Light
  *Represents an opengl light eiter point or directional
  */
class PointLight{
private:
	GLfloat _position[4];
	LightNumber _number;
	GLfloat _color[4];

public:
	PointLight( LightNumber lnumber, GLfloat r, GLfloat g, GLfloat b, GLfloat a );
	~PointLight();
	GLfloat* position();
	void on();
	void off();
	void draw();
	void position_is( const GLfloat* const new_position);
	LightNumber number();

};
#endif

