#ifndef DIRECTIONAL_LIGHT_DOT_H
#define DIRECTIONAL_LIGHT_DOT_H

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
class DirectionalLight{
private:
	GLfloat _position[4];
	LightNumber _number;
	GLfloat _color[4];

public:
	DirectionalLight( LightNumber lnumber, GLfloat r, GLfloat g, GLfloat b, GLfloat a );
	~DirectionalLight();
	GLfloat* position();
	void on();
	void off();
	void draw();
	void position_is( const GLfloat* const new_position);
	LightNumber number();

};
#endif

