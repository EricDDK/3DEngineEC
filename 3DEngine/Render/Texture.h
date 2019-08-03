#ifndef _RENDER_TEXTURE_H__
#define _RENDER_TEXTURE_H__

#include "../Common/Macro.h"
#include <string>
#include <SDL/SDL.h>
#include <SOIL/SOIL.h>

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

	void createFromSurface(struct SDL_Surface* surface);

private:

	unsigned int _textureID;

	int _width;

	int _height;

};

ENGINE_NAMESPACE_END

#endif