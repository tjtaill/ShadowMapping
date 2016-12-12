#include "StdAfx.h"
#include "CubeMap.h"

//#include <stdlib.h>
#include <cassert>


void CubeMap::loadRawTexture( std::string fileName )
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
    data = (unsigned char*)malloc( _width * _height * 3 );

    // read texture data
    fread( data, _width * _height * 3, 1, file );
    fclose( file );

    // allocate a texture name
    glGenTextures( 1, &_texture );

    // select our current texture
	glBindTexture( GL_TEXTURE_CUBE_MAP, _texture );

    // select modulate to mix texture with color for shading
    //glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // the texture wrap is clamped
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);//GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);//GL_CLAMP_TO_EDGE);
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);//GL_CLAMP_TO_EDGE);

	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_GENERATE_MIPMAP, GL_TRUE );
    // build our texture mipmaps
	for( int i = 0; i <= 5; i++){
		glTexImage2D( cubeFace[i], 0, GL_RGB, _width, _height,
			               0, GL_RGB, GL_UNSIGNED_BYTE, data );
	}

    // free buffer
    free( data );

	

}

CubeMap::CubeMap( TextureUnit unit, GLuint width, GLuint height, std::string fileName )
{
	_unit = unit;
	_width = width;
	_height = height;
	glActiveTexture( _unit );
	glEnable(GL_TEXTURE_CUBE_MAP);
	loadRawTexture( fileName );
	glDisable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture( 0 );
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

}

CubeMap::~CubeMap(void)
{
	glDeleteTextures( 1, &_texture);
}

void CubeMap::on(){
	glEnable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture( _unit );
	glBindTexture( GL_TEXTURE_CUBE_MAP, _texture );
}

void CubeMap::off(){
	glActiveTexture( 0 );
	glBindTexture( GL_TEXTURE_CUBE_MAP, 0 );
	glDisable(GL_TEXTURE_CUBE_MAP);
}
