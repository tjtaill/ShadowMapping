#ifndef SHADER_DOT_H
#define SHADER_DOT_H

#include <list>
#include <string>
#include <gl/glew.h>








enum ShaderType{
	VERTEX=GL_VERTEX_SHADER,
	FRAGMENT=GL_FRAGMENT_SHADER
};

/**
  *@file Shader.h
  *@author Troy Taillefer
  *@version 0.1
  *@date January 30, 2008
  *
  */

/**
  *@class Shader
  *Represents an opengl shader
  */
class Shader
{
private:
	
	std::list<std::string> _lines;
	ShaderType _type;
	std::string _fileName;
	GLuint _glshader;
	std::string _source;
	
	bool _wasCompiledSuccessfully;
	
	std::string _compilerErrors;
	

	void loadShader();
	void initSource();
	void compileShader();
	

	
public:
	Shader( std::string fileName, ShaderType type );
	virtual ~Shader();

	ShaderType type();
	std::string line( unsigned int line ); 
	std::string fileName();
	std::string compilerErrors();
	bool didNotCompileOk();
	std::string source();
	GLuint shader();
	
};
#endif
