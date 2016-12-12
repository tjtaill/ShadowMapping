#include "StdAfx.h"
#include "Material.h"

Material::Material(GLfloat ambientRed, 
			GLfloat ambientGreen, 
			GLfloat ambientBlue,
			GLfloat diffuseRed, 
			GLfloat diffuseGreen, 
			GLfloat diffuseBlue,
			GLfloat specularRed, 
			GLfloat specularGreen,
			GLfloat specularBlue,
			GLfloat shine)
{
	_ambient[RED] = ambientRed;
	_ambient[GREEN] = ambientGreen;
	_ambient[BLUE] = ambientBlue;
	_ambient[ALPHA] = 1.0f;
	_diffuse[RED] = diffuseRed;
	_diffuse[GREEN] = diffuseGreen;
	_diffuse[BLUE] = diffuseBlue;
	_diffuse[ALPHA] = 1.0f;
	_specular[RED] = specularRed;
	_specular[GREEN] = specularGreen;
	_specular[BLUE] = specularBlue;
	_specular[ALPHA] = 1.0f;
	_shine = shine * 128;
	
}


void Material::on()
{
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, _ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, _specular);
	glMaterialf(GL_FRONT, GL_SHININESS, _shine);
}
	
void Material::off()
{
	float ambDefault[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float diffDefault[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
	float specDefault[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambDefault);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffDefault);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specDefault);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);
	
	
}

Material::~Material(void)
{
	
}
