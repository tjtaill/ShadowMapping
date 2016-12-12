#ifndef RECTANGLE_DOT_H
#define RECTANGLE_DOT_H
class Wall
{
private:
	float _height;
	float _width;

public:
	Wall(float width, float height);
	~Wall();
	void draw();
};
#endif RECTANGLE_DOT_H