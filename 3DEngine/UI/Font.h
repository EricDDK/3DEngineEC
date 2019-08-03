#ifndef _UI_FONT_H__
#define _UI_FONT_H__

#include "../Common/Macro.h"
#include "../Render/Texture.h"
#include "../Math/Math.h"
#include "../Common/Log.h"
#include <string>
#include <unordered_map>
#include <SDL/SDL_ttf.h>

ENGINE_NAMESPACE_START

class Game;

class Font
{
public:

	Font(Game* game);

	~Font();

	bool load(const std::string& fileName);

	void unload();

	Texture* renderTexture(const std::string& textKey,
		const Vector3& color = Vector3(1.0f, 1.0f, 1.0f),
		int pointSize = 30);
	
private:

	std::unordered_map<int, TTF_Font*> _fontData;

	Game* _game;

};

ENGINE_NAMESPACE_END

#endif