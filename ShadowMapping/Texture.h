#ifndef TEXTURE_DOT_H
#define TEXTURE_DOT_H
#include <string>


#include "TextureUnit.h"



/**
  *@class Shader
  *Represents an opengl texture that can work with a shader
  */
class Texture{
private:
	GLuint _texture;
	TextureUnit _unit;
	GLuint height_, width_;
	//GLuint _texture 
	void loadRawTexture( std::string fileName );
	void setTextureParameters();
	

public:
	Texture(GLuint width, GLuint height, std::string fileName, TextureUnit unit );
	~Texture( );
	GLuint texture();
	void off();
	void on();

};

#endif
