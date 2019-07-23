#include "VertexArray.h"

ENGINE_NAMESPACE_START

VertexArray::VertexArray(const void* verts, GLuint vertsCount, Layout layout, const GLuint* indices, GLuint indicesCount)
	:_vertsCount(vertsCount)
	, _indicesCount(indicesCount)
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	GLuint vertexSize = 8 * sizeof(float);
	if (layout == PosNormSkinTex)
	{
		vertexSize += 8 * sizeof(char);
	}

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vertsCount * vertexSize, verts, GL_STATIC_DRAW);

	// Create index buffer
	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	if (layout == PosNormTex)
	{
		// Position is 3 floats
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
		// Normal is 3 floats
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 3));
		// Texture coordinates is 2 floats
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6));
	}
	else if (layout == PosNormSkinTex)
	{
		// Position is 3 floats
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
		// Normal is 3 floats
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 3));
		// Skinning indices (keep as ints)
		glEnableVertexAttribArray(2);
		glVertexAttribIPointer(2, 4, GL_UNSIGNED_BYTE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6));
		// Skinning weights (convert to floats)
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 4));
		// Texture coordinates
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 8));
	}
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
	glDeleteVertexArrays(1, &_vao);
}

void VertexArray::setActive()
{
	glBindVertexArray(_vao);
}

GLuint VertexArray::getIndicesCount() const
{
	return _indicesCount;
}

GLuint VertexArray::getVertsCount() const
{
	return _vertsCount;
}

GLuint VertexArray::getVertexArray() const
{
	return _vao;
}

GLuint VertexArray::getVertexBuffer() const
{
	return _vbo;
}

GLuint VertexArray::getIndexBuffer() const
{
	return _ebo;
}

ENGINE_NAMESPACE_END