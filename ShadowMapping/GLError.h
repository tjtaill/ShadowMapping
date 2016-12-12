#ifndef GL_ERROR_DOT_H
#define GL_ERROR_DOT_H
#include <iostream>
#include <gl/glew.h>
#include <gl/glut.h>

// GL ERROR CHECK
int CheckGLError(char *file, int line)
{
	using namespace std;
   GLenum glErr;
   int    retCode = 0;

   glErr = glGetError();
   while (glErr != GL_NO_ERROR) 
   {
	 const GLubyte* sError = gluErrorString(glErr);

	 if (sError)
		cout << "GL Error #" << glErr << "(" << gluErrorString(glErr) << ") " << " in File " << file << " at line: " << line << endl;
	 else
		cout << "GL Error #" << glErr << " (no message available)" << " in File " << file << " at line: " << line << endl;
		
	 retCode = 1;
	 glErr = glGetError();
   }
   return retCode;
}
   
#define CHECK_GL_ERROR() CheckGLError(__FILE__, __LINE__)
#endif