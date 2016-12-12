#include "StdAfx.h"
#include "Shader.h"
#include <fstream>


using namespace std;

string Shader::source(void){
	return _source;
}

std::string Shader::compilerErrors(){
	return _compilerErrors;
}


bool Shader::didNotCompileOk(){
	return !_wasCompiledSuccessfully;
}



void Shader::loadShader()
{
	ifstream file(_fileName.c_str());
	string line;

	while( !file.eof() ){
		getline(file, line);
		_lines.push_back( line );
	}

	file.close();
}





Shader::Shader( std::string fileName, ShaderType type )
{
	// initialize variables
	_type = type;
	_fileName = fileName;
	
	// create shader
	_glshader = glCreateShader(type);

	// get shader source code
	loadShader();
	
	initSource();

	// compile the shader
	compileShader();
	
}




void Shader::compileShader()
{
	const char* csource =  _source.c_str(); 



	glShaderSource( _glshader,
					1,
					&csource,
					NULL );
	
	// Compile the shader
	glCompileShader( _glshader );

	// Test if the compilation was successful
	GLint status[1];
	glGetShaderiv(_glshader, GL_COMPILE_STATUS, &status[0] );

	if ( GL_TRUE == status[0] ){
		_wasCompiledSuccessfully = true;
		_compilerErrors = "";
	}
	else
	{
		_wasCompiledSuccessfully = false;
		GLint size[1];
		glGetShaderiv(_glshader, GL_INFO_LOG_LENGTH, &size[0]);
		GLchar* log = new char[size[0]];

		glGetShaderInfoLog(_glshader, size[0], NULL, log);

		_compilerErrors = log;
	}
}



Shader::~Shader()
{

	// delete shader
	glDeleteShader(_glshader);

	// clear the source strings
	_lines.clear();

}


ShaderType Shader::type()
{
	return _type;
}

string Shader::line( unsigned int line )
{
	list<string>::iterator it = _lines.begin();
	unsigned int index = 1;
	string ret = "";
	for(; it != _lines.end(); ++it){
		if ( line == index ){
			ret = *it;
			break;
		}
		index++;
	}
	return ret;
}

void Shader::initSource()
{
	list<string>::iterator it = _lines.begin();

	
	for(; it != _lines.end(); ++it){
		_source += *it;
		_source += "\n";
	}
	_source += '\0';
	
}

std::string Shader::fileName(){
	return _fileName;
}

GLuint Shader::shader(){
	return _glshader;

}