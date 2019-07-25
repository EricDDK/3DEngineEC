#include "Font.h"

ENGINE_NAMESPACE_START

Font::Font()
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

	return texture;
}

ENGINE_NAMESPACE_END