#include "Shader.h"
#include <SDL/SDL.h>
#include <fstream>
#include <sstream>
#include "../Common/Log.h"


ENGINE_NAMESPACE_START

Shader::Shader()
	: _vertexShader(0)
	, _fragmentShader(0)
	, _shaderProgram(0)
{

}

Shader::~Shader()
{

}

bool Shader::load(const std::string& vertexFileName, const std::string& fragmentFileName)
{
	if (!compileShader(vertexFileName, GL_VERTEX_SHADER, _vertexShader)
		|| !compileShader(fragmentFileName, GL_FRAGMENT_SHADER, _fragmentShader))
	{
		return false;
	}

	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, _vertexShader);
	glAttachShader(_shaderProgram, _fragmentShader);
	glLinkProgram(_shaderProgram);

	if (!isValidProgram())
	{
		return false;
	}
	return true;
}

void Shader::unload()
{
	glDeleteProgram(_shaderProgram);
	glDeleteShader(_vertexShader);
	glDeleteShader(_fragmentShader);
}

void Shader::setActive()
{
	glUseProgram(_shaderProgram);
}

void Shader::setMatrixUniform(const char* name, const Matrix4& matrix)
{
	GLuint location = glGetUniformLocation(_shaderProgram, name);
	// Send the matrix data to the uniform
	glUniformMatrix4fv(location, 1, GL_TRUE, matrix.getShaderPtr());
}

void Shader::setMatrixUniforms(const char* name, const Matrix4* matrix, unsigned int count)
{
	GLuint location = glGetUniformLocation(_shaderProgram, name);
	// Send the matrix data to the uniform
	glUniformMatrix4fv(location, count, GL_TRUE, matrix->getShaderPtr());
}

void Shader::setVectorUniform(const char* name, const Vector3& vector)
{
	GLuint location = glGetUniformLocation(_shaderProgram, name);
	// Send the vector data
	glUniform3fv(location, 1, vector.getShaderPtr());
}

void Shader::setFloatUniform(const char* name, float value)
{
	GLuint location = glGetUniformLocation(_shaderProgram, name);
	// Send the float data
	glUniform1f(location, value);
}

bool Shader::compileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader)
{
	std::ifstream shaderFile(fileName);
	if (shaderFile.is_open())
	{
		// Read all of the text into a string
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		// Create a shader of the specified type
		outShader = glCreateShader(shaderType);
		// Set the source characters and try to compile
		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		glCompileShader(outShader);

		if (!isCompiled(outShader))
		{
			log("Failed to compile shader %s", fileName.c_str());
			return false;
		}
	}
	else
	{
		log("Shader file not found: %s", fileName.c_str());
		return false;
	}

	return true;
}

bool Shader::isCompiled(GLuint shader)
{
	GLint status;
	// Query the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		log("GLSL Compile Failed:\n%s", buffer);
		return false;
	}
	
	return true;
}

bool Shader::isValidProgram()
{
	GLint status;
	// Query the link status
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(_shaderProgram, 511, nullptr, buffer);
		log("GLSL Link Status:\n%s", buffer);
		return false;
	}

	return true;
}


ENGINE_NAMESPACE_END