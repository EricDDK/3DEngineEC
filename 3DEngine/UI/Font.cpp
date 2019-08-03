#include "Font.h"
#include "../Game.h"
#include <SDL/SDL_ttf.h>

ENGINE_NAMESPACE_START

Font::Font(Game* game)
	: _game(game)
{

}

Font::~Font()
{

}

bool Font::load(const std::string& fileName)
{
	// We support these font sizes
	std::vector<int> fontSizes = {
		8, 9,
		10, 11, 12, 14, 16, 18,
		20, 22, 24, 26, 28,
		30, 32, 34, 36, 38,
		40, 42, 44, 46, 48,
		52, 56,
		60, 64, 68,
		72
	};

	for (auto& size : fontSizes)
	{
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);
		if (font == nullptr)
		{
			log("Failed to load font %s in size %d", fileName.c_str(), size);
			return false;
		}
		_fontData.emplace(size, font);
	}
	return true;
}

void Font::unload()
{
	for (auto& font : _fontData)
	{
		TTF_CloseFont(font.second);
	}
}

Texture* Font::renderTexture(const std::string& textKey,
	const Vector3& color,
	int pointSize)
{
	Texture* texture = nullptr;
	// Convert to SDL_Color
	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(color.x * 255);
	sdlColor.g = static_cast<Uint8>(color.y * 255);
	sdlColor.b = static_cast<Uint8>(color.z * 255);
	sdlColor.a = 255;

	// Find the font data for this point size
	auto iter = _fontData.find(pointSize);
	if (iter != _fontData.end())
	{
		TTF_Font* font = iter->second;
		const std::string& actualText = _game->getText(textKey);
		// Draw this to a surface (blended for alpha)
		SDL_Surface* surf = TTF_RenderUTF8_Blended(font, actualText.c_str(), sdlColor);
		if (surf != nullptr)
		{
			// Convert from surface to texture
			texture = new Texture();
			texture->createFromSurface(surf);
			SDL_FreeSurface(surf);
		}
	}
	else
	{
		SDL_Log("Point size %d is unsupported", pointSize);
	}
	return texture;
}

ENGINE_NAMESPACE_END