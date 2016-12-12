#ifndef SPOTLIGHT_DOT_H
#define SPOTLIGHT_DOT_H


#include "LightNumber.h"

class SpotLight
{
	GLUquadric* _quadric;
	GLdouble _topRadius;
	GLdouble _bottomRadius;
	GLdouble _height;
	GLuint _stacks, _slices;

	GLfloat _position[4];
	GLfloat _spotExponent;
	GLfloat _direction[4];
	GLdouble _spotCutoff;
	GLfloat _color[4];
	LightNumber _lightNumber;
	
	

public:
	SpotLight(
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
			GLfloat spotExponent);
	void position_is(GLfloat xpos, GLfloat ypos, GLfloat zpos);
	void direction_is(GLfloat xdir, GLfloat ydir, GLfloat zdir);
	void draw();
	void on();
	void off();
	virtual ~SpotLight(void);
};
#endif