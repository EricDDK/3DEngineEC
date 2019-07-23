#ifndef _RENDER_VERTEXARRAY_H__
#define _RENDER_VERTEXARRAY_H__

#include "../Common/Macro.h"
#include <string>

ENGINE_NAMESPACE_START

class Texture
{
public:

	Texture();

	virtual ~Texture();

	bool load(const std::string fileName);

	void unload();

	void setActive();

	int getWidth() const;

	int getHeight() const;

private:

	unsigned int _textureID;

	int _width;

	int _height;

};

ENGINE_NAMESPACE_END

#endif