#include "stdafx.h"
#include "Math3D.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/foreach.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <iostream>
#include "Axis.h"

namespace ublas = boost::numeric::ublas;

using namespace std;

float distance_between_points( const float* const first, const float* const second )
{
	ublas::vector<float> f(3), s(3), d(3);

	copy(&first[0], &first[3], f.begin());
	copy(&second[0], &second[3], s.begin());
	d = f - s;
	return ublas::norm_2( d );

}

void to_column_major(const ublas::unbounded_array<float>& row_matrix,
					 float* const column_matrix)
{
	unsigned int indexes[16] = 
		{ 0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15};

	for ( unsigned int i = 0; i < 16; i++)
		column_matrix[i] = row_matrix[ indexes[i] ];
		
}

float deg_to_rad( float degrees )
{
	return degrees * M_PI / 180.0f;
}

float rad_to_deg( float rads )
{
	return rads * 180.0f / M_PI;
}

void rotate_y( float degrees, const float* const old_position, float* const new_position)
{
	ublas::vector<float> v(4);

	copy(&old_position[0], &old_position[4], v.begin());

	ublas::matrix<float> m(4, 4);
	m = ublas::identity_matrix<float>(4);

	float rad_of_deg = deg_to_rad( degrees );
	float costheta = cos( rad_of_deg );
	float sintheta = sin( rad_of_deg );

	m(0, 0) = costheta;
	m(2, 0) = -sintheta;
	m(0, 2) = sintheta;
	m(2, 2) = costheta;

	ublas::vector<float> result(4);
	result = ublas::prod(m, v);

	copy( result.begin(), result.end(), &new_position[0]);

}

void translate( float tx, float ty, float tz, const float* const old_position, float* const new_position)
{

	ublas::vector<float> v(4);

	copy(&old_position[0], &old_position[4], v.begin());

	
	ublas::matrix<float> m(4, 4);
	m = ublas::identity_matrix<float>(4);
	
	m(0, 3) = tx;
	m(1, 3) = ty;
	m(2, 3) = tz;

	ublas::vector<float> result;

	result = ublas::prod( m, v );

	copy( result.begin(), result.end(), &new_position[0]);
}

void translatation_matrix( float tx, float ty, float tz, float* const matrix)
{
	ublas::matrix<float> m(4, 4);
	m = ublas::identity_matrix<float>(4);
	
	m(0, 3) = tx;
	m(1, 3) = ty;
	m(2, 3) = tz;

	to_column_major( m.data(), matrix );
}

void scale_matrix( float sx, float sy, float sz, float* const matrix)
{
	ublas::matrix<float> m(4, 4);
	m = ublas::identity_matrix<float>(4);
	
	m(0, 0) *= sx;
	m(1, 1) *= sy;
	m(2, 2) *= sz;

	to_column_major( m.data(), matrix );
	
}

void identity_matrix( float* const matrix)
{
	ublas::matrix<float> m(4, 4);
	m = ublas::identity_matrix<float>(4);

	to_column_major( m.data(), matrix );
}

void load_matrix( const float* const in, ublas::matrix<float>& out)
{
	for( unsigned int i = 0; i < 4; i++)
		for( unsigned int j = 0; j < 4; j++)
		{
			out(j, i) = in[ 4 * i + j];
		}

}


void tranpose_matrix( const float* const original, float* const result)
{
	ublas::matrix<float> m(4,4);
	load_matrix( original, m );

	m = ublas::trans( m );

	to_column_major( m.data(), result );

}




void matrix_multiply( const float* const matrix_one,
					 const float* const matrix_two,
					 float* const result_matrix)
{
	ublas::matrix<float> m_one(4, 4);
	ublas::matrix<float> m_two(4, 4);
	ublas::matrix<float> result(4, 4);

	for( unsigned int i = 0; i < 4; i++)
		for( unsigned int j = 0; j < 4; j++)
		{
			m_one(j, i) = matrix_one[ 4 * i + j];
			m_two(j, i) = matrix_two[ 4 * i + j];
		}

		result = ublas::prod( m_one, m_two );
		 
		to_column_major( result.data(), result_matrix );

}

