#ifndef GLUTAPPLICATION_DOT_H
#define GLUTAPPLICATION_DOT_H


#include <string>
#include <gl/glew.h>
#include <gl/glut.h>


/**
  *@file GlutApplication.h
  *@author Troy Taillefer
  *@version 0.1
  *@date Decemeber 8, 2007
  *
  */

/**
  *@class GlutApplication
  *@warning a child of this class must be instantiated before many opengl calls will work
  *This class abstracts a glut application registers all relevant call backs
  *these call backs can be overriden in classes that inherit form this one.
  * This class uses boost thread to implement the singleton pattern
  */
class GlutApplication
{
private:
	// singleton variable
	static unsigned int instances_;

	// these are call back wrappers to overcome the differences between non static member functions
	// and c style function pointers required by glut callbacks
	static void initInstances(void) { instances_ = 0; }
	static void OnDisplayCallWrapper( void );
	static void OnNormalKeyPressedCallWrapper(unsigned char keyPressed, int x, int y);
	static void OnSpecialKeyPressedCallWrapper(int keyPressed, int x, int y);
	static void OnMouseDragCallWrapper(int x, int y);
	static void OnIdleCallWrapper(void);
	static void OnMousePressedCallWrapper(int button, int state, int x, int y);
	static void OnReshapeWindowCallWrapper(int newWidth, int newHeight);

protected:
	int windowWidth_;
	int windowHeight_;
	std::string windowTitle_;
	int xWindowPosition_;
	int yWindowPosition_;
	unsigned int displayMode_;
	

	/**
	  *@warning this static self reference must be initiliased in the constructor of derived classes
	  */
	static GlutApplication* glutApplicationPointer;

	
	virtual void OnInit(void){};
	virtual void OnReshapeWindow(int newWidth, int newHeight);
	virtual void OnDisplay(void) {};
	virtual void OnNormalKeyPressed(unsigned char keyPressed, int x, int y) {};
	virtual void OnSpecialKeyPressed(int keyPressed, int x, int y) {};
	virtual void OnMousePressed(int button, int state, int x, int y) {};
	virtual void OnMouseDrag(int x, int y) {};
	virtual void OnIdle(void) {};
	
	GlutApplication(void) {};
	GlutApplication(int argc, char** argv, 
		std::string windowTitle = "", int windowHeight=400, int windowWidth=400, 
		int xWindowPositon=100, int yWindowPosition=100, unsigned int displayMode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

public:
	/**
	  * destructor
	  */
	virtual ~GlutApplication(void);
	/**
	  *enter the glut main loop
	  *@todo consider making this method static so it can't be overriden
	  */
	void EnterMainLoop(void);
};
#endif

