#ifndef MATH_3D_DOT_H
#define MATH_3D_DOT_H

void rotate_y( float degrees, const float* const old_position, float* const new_position);

void translate( float x, float y, float z, const float* const old_position, float* const new_position);

void matrix_multiply( const float* const matrix_one, 
					 const float* const matrix_two,
					 float* const result_matrix);

void scale_matrix( float sx, float sy, float sz, float* const matrix);

void translatation_matrix( float tx, float ty, float tz, float* const matrix);

void identity_matrix( float* const matrix);

float deg_to_rad( float degrees );

float rad_to_deg( float rads );

void tranpose_matrix( const float* const original, float* const result);


float distance_between_points( const float* const first, const float* const second );

#endif