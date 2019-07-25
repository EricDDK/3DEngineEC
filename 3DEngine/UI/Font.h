#ifndef _RENDER_FONT_H__
#define _RENDER_FONT_H__

#include "../Common/Macro.h"
#include "../Render/Texture.h"
#include "../Math/Math.h"
#include "../Common/Log.h"
#include <string>
#include <unordered_map>
#include <SDL/SDL_ttf.h>

ENGINE_NAMESPACE_START

class Font
{
public:

	Font();

	~Font();

	bool load(const std::string& fileName);

	void unload();

	Texture* renderTexture(const std::string& textKey,
		const Vector3& color = Vector3(1.0f, 1.0f, 1.0f),
		int pointSize = 30);
	
private:

	std::unordered_map<int, TTF_Font*> _fontData;

	// TODO

};

ENGINE_NAMESPACE_END

#endif