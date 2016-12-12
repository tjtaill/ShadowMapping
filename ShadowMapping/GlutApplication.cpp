#include "StdAfx.h"
#include "GlutApplication.h"
#include <cassert>
#include <iostream>
#include <boost/thread/once.hpp>
boost::once_flag appOnceFlag = BOOST_ONCE_INIT;

unsigned int GlutApplication::instances_;
GlutApplication* GlutApplication::glutApplicationPointer;

GlutApplication::GlutApplication(int argc, char** argv, 
		std::string windowTitle, int windowHeight, int windowWidth, 
		int xWindowPosition, int yWindowPosition, unsigned int displayMode) :
		windowTitle_(windowTitle),
		windowHeight_(windowHeight),
		windowWidth_(windowWidth),
		xWindowPosition_(xWindowPosition),
		yWindowPosition_(yWindowPosition),
		displayMode_(displayMode)
{
 
	// add thread safety to this constructor to insure that only one instance exists
	boost::call_once( &GlutApplication::initInstances, appOnceFlag);
	instances_++;
	assert( 1 == instances_ );
	glutInit(&argc, argv);
	//glutInitDisplayMode( displayMode_ );
	glutInitDisplayString("rgb double depth=32");
	glutInitWindowSize( windowWidth_, windowHeight );
	glutInitWindowPosition( xWindowPosition_, yWindowPosition_ );
	glutCreateWindow( windowTitle_.c_str() );
	// important to add this function for shaders
	glewInit();

	// Register call backs
	glutDisplayFunc( &GlutApplication::OnDisplayCallWrapper );
	glutReshapeFunc( &GlutApplication::OnReshapeWindowCallWrapper );
	glutKeyboardFunc( &GlutApplication::OnNormalKeyPressedCallWrapper );
	glutSpecialFunc( &GlutApplication::OnSpecialKeyPressedCallWrapper );
	glutMouseFunc( &GlutApplication::OnMousePressedCallWrapper );
	glutMotionFunc( &GlutApplication::OnMouseDragCallWrapper );
	glutIdleFunc(  &GlutApplication::OnIdleCallWrapper );
}







void GlutApplication::OnReshapeWindow(int newWidth, int newHeight)
{
	glutApplicationPointer->OnReshapeWindow(newWidth, newHeight);
}

GlutApplication::~GlutApplication(void)
{
}

void GlutApplication::OnDisplayCallWrapper( void )
{	
	glutApplicationPointer->OnDisplay();
}

void GlutApplication::OnMousePressedCallWrapper(int button, int state, int x, int y)
{
	
	glutApplicationPointer->OnMousePressed(button, state, x, y);
}

void GlutApplication::OnNormalKeyPressedCallWrapper(unsigned char keyPressed, int x, int y)
{
	
	glutApplicationPointer->OnNormalKeyPressed(keyPressed, x, y);
}

void GlutApplication::OnSpecialKeyPressedCallWrapper(int keyPressed, int x, int y){
	glutApplicationPointer->OnSpecialKeyPressed(keyPressed, x, y);
}

void GlutApplication::OnMouseDragCallWrapper(int x, int y)
{
	
	glutApplicationPointer->OnMouseDrag(x, y);
}

void GlutApplication::OnIdleCallWrapper(void)
{
	
	glutApplicationPointer->OnIdle();
}

void GlutApplication::OnReshapeWindowCallWrapper(int newWidth, int newHeight)
{
	GlutApplication::glutApplicationPointer->OnReshapeWindow( newWidth, newHeight );
}

void GlutApplication::EnterMainLoop(void)
{
	glutMainLoop();
}
