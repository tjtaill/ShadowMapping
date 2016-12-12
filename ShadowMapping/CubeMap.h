#ifndef CUBE_MAP_DOT_H
#define CUBE_MAP_DOT_H

#include <string>
#include "TextureUnit.h"

enum FaceIndex{
	PX=0,
	NX=1,
	PY=2,
	NY=3,
	PZ=4,
	NZ=5
};

static GLenum cubeFace[6] = { 
	GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

class CubeMap
{
	GLuint _texture;
	TextureUnit _unit;
	GLuint _width, _height;
	void loadRawTexture( std::string fileName );
	

public:
	CubeMap( TextureUnit unit, GLuint width, GLuint height, std::string fileName );
	virtual ~CubeMap(void);
	void on();
	void off();
};
#endif
