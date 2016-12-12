#ifndef SPHERE_DOT_H
#define SPHERE_DOT_H

#include <gl/glew.h>
#include <gl/glut.h>

/**
  *@class Sphere
  *Represents an opengl sphere
  */
class Sphere{
private:
	double radius_;
	int slices_;
	int stacks_;
	GLUquadric* quadric_;

public:
	Sphere(double radius, int slices, int stacks);
	virtual ~Sphere();
	void draw();
	

};



#endif
