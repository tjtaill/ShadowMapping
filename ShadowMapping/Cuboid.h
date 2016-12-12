#ifndef CUBOID_DOT_H
#define CUBOID_DOT_H

#include <gl/glut.h>

class Cuboid
{
private:
	double _height;
	double _width;
	double _depth;
	double _max;


public:
	Cuboid(double width, double height, double depth);
	virtual ~Cuboid(void);
	void draw();

};
#endif
