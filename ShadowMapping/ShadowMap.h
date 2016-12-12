#ifndef SHADOW_MAP_DOT_H
#define SHADOW_MAP_DOT_H
#include "TextureUnit.h"
#include "Frustum.h"


enum ShadowDepth{
	DEFAULT_BITS=GL_DEPTH_COMPONENT,
	SIXTEEN_BITS=GL_DEPTH_COMPONENT16,
	TWENTYFOUR_BITS=GL_DEPTH_COMPONENT24,
	THIRTYTWO_BITS=GL_DEPTH_COMPONENT32
};

class ShadowMap
{
private:
	ShadowDepth _depth;
	unsigned int _width;
	unsigned int _height;
	TextureUnit _unit;
	GLuint _texture;
	float _texture_matrix[16];
	bool _pcf_on;
	bool _cull_front_face;


public:
	ShadowMap(TextureUnit unit);
	~ShadowMap(void);
	void on(void);
	void off(void);
	void ShadowMap::post_render( const Frustum* const frustum );
	void ShadowMap::pre_render( const Frustum* const frustum );
	void pre_draw_scene();
	void post_draw_scene();
	void pcf_on();
	void pcf_off();
	void cull_front();
	void cull_none();
	bool is_culling_on();
};
#endif
