#include "StdAfx.h"
#include "Math3D.h"
#include "ShadowMap.h"



ShadowMap::ShadowMap(TextureUnit unit)
{
	_unit = unit;
	_cull_front_face = false;

	glGenTextures(1, &_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
	_pcf_on = false;

	

}

ShadowMap::~ShadowMap(void)
{
	glDeleteTextures(1, &_texture);
}

void ShadowMap::on(void){
	glEnable(GL_TEXTURE_2D);
	glActiveTexture( _unit );
	glBindTexture( GL_TEXTURE_2D, _texture);
    

    
	


}

void ShadowMap::off(void)
{
	glDisable(GL_TEXTURE_2D);
	glActiveTexture( 0 );

}

void ShadowMap::pre_render(const Frustum* const frustum)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	if ( _pcf_on )
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FAIL_VALUE_ARB, 0.5f);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

	 // Clear the depth buffer only
    glClear(GL_DEPTH_BUFFER_BIT);

	// All we care about here is resulting depth values
    glShadeModel(GL_FLAT);
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_NORMALIZE);
    glColorMask(0, 0, 0, 0);

	// Overcome imprecision
    glEnable(GL_POLYGON_OFFSET_FILL);
	if ( _cull_front_face )
	{
		glEnable( GL_CULL_FACE );
		glCullFace( GL_FRONT );
	}

	

	

}

void ShadowMap::post_render( const Frustum* const frustum )
{
	// Copy depth values into depth texture
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
		0, 0, frustum->viewport_width(), frustum->viewport_height(), 0);
	

	 // Restore normal drawing state
	 glDisable( GL_CULL_FACE );
	 glCullFace( GL_NONE );

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    //glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glColorMask(1, 1, 1, 1);
    glDisable(GL_POLYGON_OFFSET_FILL);

	// Set up texture matrix for shadow map projection,
    // which will be rolled into the eye linear
    // texture coordinate generation plane equations
	const float* const projection_matrix = frustum->projection_matrix();
	const float* const modelview_matrix = frustum->modelview_matrix();

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glTranslatef(0.5f, 0.5f, 0.5f);
	glScalef(0.5f, 0.5f, 0.5f);
	glMultMatrixf(projection_matrix);
	glMultMatrixf(modelview_matrix);
	glMatrixMode(GL_MODELVIEW);


	
}



void ShadowMap::pre_draw_scene()
{

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_GEN_R);
    glEnable(GL_TEXTURE_GEN_Q);
	

	

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, 
                        GL_COMPARE_R_TO_TEXTURE);

	GLfloat sPlane[4] = {1.0f, 0.0f, 0.0f, 0.0f};
    GLfloat tPlane[4] = {0.0f, 1.0f, 0.0f, 0.0f};
    GLfloat rPlane[4] = {0.0f, 0.0f, 1.0f, 0.0f};
    GLfloat qPlane[4] = {0.0f, 0.0f, 0.0f, 1.0f};

	glTexGenfv(GL_S, GL_EYE_PLANE, sPlane);
    glTexGenfv(GL_T, GL_EYE_PLANE, tPlane);
    glTexGenfv(GL_R, GL_EYE_PLANE, rPlane);
    glTexGenfv(GL_Q, GL_EYE_PLANE, qPlane);

}

void ShadowMap::post_draw_scene()
{
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_R);
    glDisable(GL_TEXTURE_GEN_Q);
}

void ShadowMap::pcf_on()
{
	_pcf_on = true;
}

void ShadowMap::pcf_off()
{
	_pcf_on = false;
}

void ShadowMap::cull_front()
{
	_cull_front_face = true;
}

void ShadowMap::cull_none()
{
	_cull_front_face = false;
}

bool ShadowMap::is_culling_on()
{
	return _cull_front_face;
}