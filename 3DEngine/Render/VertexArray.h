#ifndef _RENDER_VERTEXARRAY_H__
#define _RENDER_VERTEXARRAY_H__

#include "../Common/Macro.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

ENGINE_NAMESPACE_START

class VertexArray
{
public:
	
	enum Layout
	{
		PosNormTex,
		PosNormSkinTex
	};
	
	VertexArray(const void* verts, GLuint vertsCount, Layout layout, const GLuint* indices, GLuint indicesCount);

	~VertexArray();

	void setActive();

	GLuint getIndicesCount() const;

	GLuint getVertsCount() const;

	GLuint getVertexArray() const;

	GLuint getVertexBuffer() const;

	GLuint getIndexBuffer() const;

private:

	GLuint _vertsCount;

	GLuint _indicesCount;

	GLuint _vao;

	GLuint _vbo;

	GLuint _ebo;

};

ENGINE_NAMESPACE_END

#endif