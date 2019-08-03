#include "Texture.h"
#include "Common/Log.h"

#include <GL/glew.h>
#include "SDL/SDL.h"
#include <SOIL/SOIL.h>

ENGINE_NAMESPACE_START

Texture::Texture()
	:_textureID(0)
	, _width(0)
	, _height(0)
{

}

Texture::~Texture()
{

}

bool Texture::load(const std::string fileName)
{
	int channel = 0;
	unsigned char *image = SOIL_load_image(fileName.c_str(), &_width, &_height, &channel, SOIL_LOAD_AUTO);

	if (image == nullptr)
	{
		log("[Texture::load()] failed %s : %s ", fileName.c_str(), SOIL_last_result());
		return false;
	}

	//log((char *)image);

	int format = GL_RGB;
	if (channel == 4)
	{
		format = GL_RGBA;
	}

	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, format, _width, _height, 0, format,
		GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

void Texture::unload()
{
	glDeleteTextures(1, &_textureID);
}

void Texture::setActive()
{
	glBindTexture(GL_TEXTURE_2D, _textureID);
}

int Texture::getWidth() const
{
	return _width;
}

int Texture::getHeight() const
{
	return _height;
}

void Texture::createFromSurface(struct SDL_Surface* surface)
{
	_width = surface->w;
	_height = surface->h;

	// Generate a GL texture
	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_BGRA,
		GL_UNSIGNED_BYTE, surface->pixels);

	// Use linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

ENGINE_NAMESPACE_END