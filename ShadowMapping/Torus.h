#ifndef TORUS_DOT_H
#define TORUS_DOT_H

#include <gl/glew.h>
#include <gl/glut.h>

class Torus
{
private:
	GLdouble _inner_radius;
	GLdouble _outer_radius;
	GLint _sides;
	GLint _rings;


public:
	Torus(GLdouble inner_radius, GLdouble outer_radius, GLint sides, GLint rings);
	virtual ~Torus(void);
	void draw(void);
};
#endif
