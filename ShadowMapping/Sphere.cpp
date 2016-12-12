#include "stdafx.h"
#include "Sphere.h"






Sphere::Sphere(double radius, int slices, int stacks) :
	radius_(radius),
	slices_(slices),
	stacks_(stacks)
{
	
	quadric_ = gluNewQuadric();
	gluQuadricTexture(quadric_, GL_TRUE);
	

}

Sphere::~Sphere(){
	gluDeleteQuadric( quadric_ );

}

void Sphere::draw(){
	gluSphere( quadric_, radius_, slices_, stacks_);
	
}

