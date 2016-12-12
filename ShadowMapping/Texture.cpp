#include "stdafx.h"
#include "Texture.h"
#include <boost/shared_ptr.hpp>
#include <stdlib.h>
#include <cassert>
#include <algorithm>
#include <iostream>

using namespace std;



void Texture::loadRawTexture( std::string fileName )
{
	//int width, height;
    unsigned char * data;
    FILE * file;

    // open texture data
    file = fopen( fileName.c_str(), "rb" );
    assert( file != NULL );

    // allocate buffer
	/*
    width = 256;
    height = 256;
	*/
    data = (unsigned char*)malloc( width_ * height_ * 3 );

    // read texture data
    fread( data, width_ * height_ * 3, 1, file );
    fclose( file );

    // allocate a texture name
    glGenTextures( 1, &_texture );

    // select our current texture
    glBindTexture( GL_TEXTURE_2D, _texture );

    // select modulate to mix texture with color for shading
    //glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // the texture wraps over at the edges (repeat)
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE );

    // build our texture mipmaps
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width_, height_,
                       0, GL_RGB, GL_UNSIGNED_BYTE, data );

    // free buffer
    free( data );

	

}







Texture::Texture(GLuint width, GLuint height, std::string fileName, TextureUnit unit )
{
	
	_unit = unit;
	width_ = width;
	height_ = height;
	glActiveTexture( _unit );
	loadRawTexture( fileName );
	
	glDisable(GL_TEXTURE_2D);
	glActiveTexture( 0 );
	glBindTexture(GL_TEXTURE_2D, 0);
	
}

void Texture::off(){
	glDisable(GL_TEXTURE_2D);
	glActiveTexture( 0 );
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::on(){
	glEnable(GL_TEXTURE_2D);
	glActiveTexture( _unit );
	glBindTexture(GL_TEXTURE_2D, _texture);	
}

Texture::~Texture( )
{
	glDeleteTextures(1, &_texture );
}

GLuint Texture::texture(){
	return _texture;
}