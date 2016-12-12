#include "StdAfx.h"
#include "Cuboid.h"




Cuboid::Cuboid(double width, double height, double depth)
{
	_width = width;
	_height = height;
	_depth = depth;

	_max = width;
	_max = _max >= height ? _max : height;
	_max = _max >= depth ? _max : depth;

}



void unitCube(){
	
	glBegin(GL_QUADS);		// Draw The Cube Using quads
		glNormal3f( 0.0f, 1.0f, 0.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, 1.0f,-1.0f);  // Top Right Of The Quad (Top)
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f(-1.0f, 1.0f,-1.0f);  // Top Left Of The Quad (Top)
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f(-1.0f, 1.0f, 1.0f);  // Bottom Left Of The Quad (Top)
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, 1.0f, 1.0f);  // Bottom Right Of The Quad (Top)
		
		glNormal3f( 0.0f, -1.0f, 0.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f,-1.0f, 1.0f);  // Top Right Of The Quad (Bottom)
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f(-1.0f,-1.0f, 1.0f);  // Top Left Of The Quad (Bottom)
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f(-1.0f,-1.0f,-1.0f);  // Bottom Left Of The Quad (Bottom)
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f,-1.0f,-1.0f);  // Bottom Right Of The Quad (Bottom)
		
		glNormal3f( 0.0f, 0.0f, 1.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, 1.0f, 1.0f);  // Top Right Of The Quad (Front)
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Left Of The Quad (Front)
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f(-1.0f,-1.0f, 1.0f);  // Bottom Left Of The Quad (Front)
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f,-1.0f, 1.0f);  // Bottom Right Of The Quad (Front)
		
		glNormal3f( 0.0f, 0.0f, -1.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f,-1.0f,-1.0f);  // Top Right Of The Quad (Back)
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f(-1.0f,-1.0f,-1.0f);  // Top Left Of The Quad (Back)
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f(-1.0f, 1.0f,-1.0f);  // Bottom Left Of The Quad (Back)
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, 1.0f,-1.0f);  // Bottom Right Of The Quad (Back)
		
		glNormal3f( -1.0f, 0.0f, 0.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Right Of The Quad (Left)
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f(-1.0f, 1.0f,-1.0f);  // Top Left Of The Quad (Left)
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f(-1.0f,-1.0f,-1.0f);  // Bottom Left Of The Quad (Left)
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f(-1.0f,-1.0f, 1.0f);  // Bottom Right Of The Quad (Left)
		
		glNormal3f( 1.0f, 0.0f, 0.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, 1.0f,-1.0f);  // Top Right Of The Quad (Right)
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, 1.0f);  // Top Left Of The Quad (Right)
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f,-1.0f, 1.0f);  // Bottom Left Of The Quad (Right)
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f,-1.0f,-1.0f);  // Bottom Right Of The Quad (Right)		
	glEnd();
}

void Cuboid::draw(){
	glPushMatrix();
		glScaled( _width / _max, _height / _max, _depth / _max );
		glScaled( _max, _max, _max );
		unitCube();
	glPopMatrix();
}




Cuboid::~Cuboid(void)
{
	
}
