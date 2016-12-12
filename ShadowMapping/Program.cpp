#include "stdafx.h"
#include "Program.h"

#include <algorithm>

using namespace std;

Program::Program(){
	_active = false;
	_glprogram = glCreateProgram();
}

bool Program::active()
{
	return _active;
}

Program::~Program(){
	glDeleteProgram(_glprogram);

	
	// detach shaders
	list<GLuint>::iterator it = _shaders.begin();
	for(; it != _shaders.end(); ++it){
		glDetachShader( _glprogram, *it );
	}
	_shaders.clear();
	uniformVariables.clear();
	


}

GLint Program::rloc( std::string variableName ){
	GLint loc = glGetUniformLocation( _glprogram, variableName.c_str());
	uniformVariables[variableName] = loc;
	return loc;
}

GLint Program::uloc( string key ){
	return uniformVariables[key];
}

void Program::addShader(GLuint shader){
	glAttachShader(_glprogram, shader);
	_shaders.push_back( shader );
}

void Program::link(){
	// link the program
	glLinkProgram( _glprogram );
	GLint status[1];
	glGetProgramiv( _glprogram, GL_LINK_STATUS, &status[0]);
	if ( GL_TRUE == status[0] ){
		_wasLinkedSuccessfully = true;
		_linkerErrors = "";
	}
	else
	{
		GLint size[1];
		glGetProgramiv( _glprogram, GL_INFO_LOG_LENGTH, &size[0]);
		GLchar* log = new char[size[0]];

		glGetProgramInfoLog( _glprogram, size[0], NULL, log);
		_linkerErrors = log;
	}

	

}

bool Program::didNotLinkOk(){
	return !_wasLinkedSuccessfully;
}

string Program::linkerErrors(){
	return _linkerErrors;
}

GLuint Program::program(){
	return _glprogram;
}

void Program::start(){
	glUseProgram( _glprogram );
	_active = true;
}

void Program::end(){
	glUseProgram( 0 );
	_active = false;
}