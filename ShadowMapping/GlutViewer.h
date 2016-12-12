#ifndef GLUTVIEWER_DOT_H
#define GLUTVIEWER_DOT_H

#include <string>
#include <map>

#include "GlutApplication.h"

#include "Shader.h"
#include "Program.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"
#include "Texture.h"
#include "Sphere.h"
#include "Cuboid.h"
#include "CubeMap.h"
#include "Wall.h"
#include "Material.h"
#include "ShadowMap.h"
#include "Torus.h"


/**
  *@file GlutViewer.h
  *@author Troy Taillefer
  *@version 0.2
  *@date January, 2008
  *
  */

/**
  *@class GlutViewer
  *This class extends glut application by using the scene graph to 
  *provides a viewer for that scene which can zoom in and out and rotate with the mouse
  */


class GlutViewer :
	public GlutApplication
{
private:
	
	Program ssm_program;
	Shader ssm_vert;
	Shader ssm_frag;
	Program pcfsm_program;
	Shader pcfsm_frag;
	Shader gaussm_frag;
	Program gaussm_program;
	Shader ditsm_frag;
	Program ditsm_program;
	

	Material chromeMaterial;
	Material silverMaterial;
	Material whiteMaterial;
	Material redMaterial;
	Material greenMaterial;
	Material blueMaterial;
	Material rubyMaterial;
	Cuboid floor;
	PointLight whiteLight;
	Frustum* light_view;
	ShadowMap shadow_map;
	Sphere ball;
	Torus torus;
	
	
	double time;
	bool timeVarying;

	double phi, theta;
	double sdepth;
	double zNear, zFar;
	double aspect;
	int downX, downY;
	bool leftButton, middleButton;
	

	void draw();
	void drawDepth(void);
	

public:
	GlutViewer(int argc, 
		char** argv,
		double scene_size); 
	void update(void);
	virtual ~GlutViewer(void);
	virtual void OnInit(void);
	virtual void OnDisplay(void);
	virtual void OnReshapeWindow(int newWidth, int newHeight);
	virtual void OnNormalKeyPressed(unsigned char keyPressed, int x, int y);
	virtual void OnSpecialKeyPressed(int keyPressed, int x, int y);
	virtual void OnMousePressed(int button, int state, int x, int y);
	virtual void OnMouseDrag(int x, int y);
};
#endif
