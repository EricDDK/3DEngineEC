#ifndef _RENDER_SHADER_H__
#define _RENDER_SHADER_H__

#include "../Common/Macro.h"
#include <string>
#include "../Math/Math.h"
#include "glad/glad.h"

ENGINE_NAMESPACE_START

class Shader
{
public:

	Shader();

	~Shader();

	bool load(const std::string& vertexFileName, const std::string& fragmentFileName);

	void unload();

	void setActive();

	void setMatrixUniform(const char* name, const Matrix4& matrix);

	void setMatrixUniform(const char* name, const Matrix4& matrix, unsigned int count);

	void setVectorUniform(const char* name, const Vector3& vector);

	void setFloatUniform(const char* name, float value);

private:

	bool compileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);

	bool isCompiled(GLuint shader);

	bool isValidProgram();

private:

	GLuint _vertexShader;

	GLuint _fragmentShader;

	GLuint _shaderProgram;
	
};

ENGINE_NAMESPACE_END

#endif