#include "StdAfx.h"
#include <math.h>
#include <algorithm>
#include <gl/glew.h>
#include <gl/glut.h>

#include "Frustum.h"
#include "Axis.h"
#include "Math3D.h"



using namespace std;

Frustum::Frustum(int viewport_width, int viewport_height, const float* const position, float scene_bounding_radius)
{
	_viewport[0] = 0;
	_viewport[1] = 0;
	_viewport[2] = viewport_width;
	_viewport[3] = viewport_height;
	
	_look_from_position[X] = position[X];
	_look_from_position[Y] = position[Y];
	_look_from_position[Z] = position[Z];

	_look_at_position[X] = 0.0f;
	_look_at_position[Y] = 0.0f;
	_look_at_position[Z] = 0.0f;
	
	_up_vector[X] = 0.0f;
	_up_vector[Y] = 1.0f;
	_up_vector[Z] = 0.0f;

	_scene_bounding_radius = scene_bounding_radius;
	
	_calculations_stale = true;

}

Frustum::~Frustum(void)
{

}

void Frustum::change()
{
	// save old state
	glGetFloatv(GL_PROJECTION_MATRIX, _old_projection_matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, _old_modelview_matrix);
	glGetIntegerv(GL_VIEWPORT, _old_viewport );
	
	if ( _calculations_stale )
	{
		_distance_to_scene = distance_between_points( _look_from_position, 
			_look_at_position);

		_near_distance = _distance_to_scene - _scene_bounding_radius;

		_field_of_view = 
			rad_to_deg( 2.0f * atan( _scene_bounding_radius / _distance_to_scene ) );

		_far_distance = _near_distance + ( 2.0f * _scene_bounding_radius );

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(_field_of_view, 1.0f, _near_distance, _far_distance);
		glGetFloatv(GL_PROJECTION_MATRIX, _projection_matrix);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt( _look_from_position[X],
			_look_from_position[Y],
			_look_from_position[Z],
			_look_at_position[X],
			_look_at_position[Y],
			_look_at_position[Z],
			_up_vector[X],
			_up_vector[Y],
			_up_vector[Z]);
		glGetFloatv(GL_MODELVIEW_MATRIX, _modelview_matrix);

		_calculations_stale = false;

	}
	else
	{
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf( _projection_matrix );
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf( _modelview_matrix );
	}
	
	glViewport( _viewport[0], _viewport[1], _viewport[2], _viewport[3]);


}

void Frustum::restore()
{
	// restore old state
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( _old_projection_matrix );
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf( _old_modelview_matrix );
	glViewport( _old_viewport[0], 
		_old_viewport[1], _old_viewport[2], _old_viewport[3]);
}

const float* const Frustum::projection_matrix() const
{
	return _projection_matrix;
}

const float* const Frustum::modelview_matrix() const
{
	return _modelview_matrix;
}

int Frustum::viewport_height() const
{
	return _viewport[3];
}

int Frustum::viewport_width() const
{
	return _viewport[2];
}

void Frustum::look_from( const float* const position )
{
	copy( &position[0], &position[3], &_look_from_position[0]);
	_calculations_stale = true;
}

void Frustum::view_size_is( int viewport_width, int viewport_height )
{
	_viewport[2] = viewport_width;
	_viewport[3] = viewport_width;
	_calculations_stale = true;

}