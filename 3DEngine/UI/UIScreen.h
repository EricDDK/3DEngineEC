#ifndef _UI_UISREEN_H__
#define _UI_UISREEN_H__

#include "../Common/Macro.h"
#include <string>
#include <functional>
#include <vector>
#include <cstdint>
#include "../Math/Math.h"
#include "Button.h"

ENGINE_NAMESPACE_START

class Game;
class Shader;
class Texture;
class Font;

class UIScreen
{
public:

	enum UIState
	{
		Active,
		Closing,
	};

	UIScreen(Game *game);

	virtual ~UIScreen();

	virtual void update(float deltaTime);

	virtual void draw(Shader *shader);

	virtual void processInput(const unsigned char* keyState);

	virtual void handleKeyPress(int key);

	void close();

	void setState(UIState state);

	UIState getState() const;

	void addButton(const std::string& name, std::function<void()> onClick);

protected:

	void drawTexture(Shader *shader, Texture *texture, const Vector2& offset = Vector2::Zero, float scale = 1.0f);

	Game *_game;

	Font *_font;

	Texture *_title;

	Texture *_bg;

	Texture *_buttonOn;

	Texture *_buttonOff;

	Vector2 _titlePos;

	Vector2 _nextButtonPos;

	Vector2 _bgPos;

	UIState _state;

	std::vector<Button*> _buttons;

};

ENGINE_NAMESPACE_END

#endif