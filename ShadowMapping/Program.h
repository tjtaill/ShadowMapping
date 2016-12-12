#ifndef PROGRAM_DOT_H
#define PROGRAM_DOT_H
/**
  *@file Program.h
  *@author Troy Taillefer
  *@version 0.1
  *@date January 30, 2008
  *
  */
#include <list>
#include <string>
#include <gl/glew.h>
#include <gl/glut.h>
#include <map>

/**
  *@class Program
  *Represents an opengl shader program
  */
class Program{
private:
	std::list<GLuint> _shaders;

	GLuint _glprogram;
	bool _wasLinkedSuccessfully;
	std::string _linkerErrors;
	std::map<std::string, GLint> uniformVariables;
	bool _active;

public:
	Program();
	~Program();
	void addShader(GLuint shader);
	void link();
	bool didNotLinkOk();
	std::string linkerErrors();
	GLuint program();
	void start();
	void end();
	GLint uloc( std::string );
	GLint rloc( std::string variableName);
	bool active();
	
};

#endif
