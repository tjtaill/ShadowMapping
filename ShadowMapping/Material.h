#ifndef MATERIAL_DOT_H
#define MATERIAL_DOT_H

#include <gl/glut.h>
#include "ColorIndex.h"


class Material
{
private:
	GLfloat _ambient[4];//_ambientRed, _ambientGreen, _ambientBlue;
	GLfloat _diffuse[4]; //_diffuseRed, _diffuseGreen, _diffuseBlue;
	GLfloat _specular[4];//_specularRed, _specularGreen, _specularBlue;
	GLfloat _shine;

public:
	Material(GLfloat ambientRed, 
			GLfloat ambientGreen, 
			GLfloat ambientBlue,
			GLfloat diffuseRed, 
			GLfloat diffuseGreen, 
			GLfloat diffuseBlue,
			GLfloat specularRed, 
			GLfloat specularGreen,
			GLfloat specularBlue,
			GLfloat shine);
	virtual ~Material(void);
	void on();
	void off();
};
#endif
