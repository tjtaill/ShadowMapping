#ifndef FRUSTUM_DOT_H
#define FRUSTUM_DOT_H


class Frustum
{
private:
	float _look_from_position[3];
	float _scene_bounding_radius;
	float _near_distance;
	float _distance_to_scene;
	float _far_distance;
	float _field_of_view;
	float _look_at_position[3];
	float _up_vector[3];
	float _old_projection_matrix[16];
	float _old_modelview_matrix[16];
	float _projection_matrix[16];
	float _modelview_matrix[16];
	bool _calculations_stale;
	int _viewport[4];
	int _old_viewport[4];



public:
	Frustum(int viewport_width, int viewport_height, const float* const position, float scene_bounding_radius);
	virtual ~Frustum(void);
	void change();
	void restore();
	const float* const projection_matrix() const;
	const float* const modelview_matrix() const;
	int viewport_height() const;
	int viewport_width() const;
	void look_from( const float* const position );
	void view_size_is( int viewport_width, int viewport_height );

};
#endif