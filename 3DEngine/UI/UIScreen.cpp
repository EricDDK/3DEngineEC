#include "UIScreen.h"
#include "../Game.h"
#include "../Render/Shader.h"
#include "../Render/Texture.h"
#include "Font.h"
#include <SDL/SDL.h>

ENGINE_NAMESPACE_START

UIScreen::UIScreen(Game *game)
	: _game(game)
	, _font(nullptr)
	, _title(nullptr)
	, _bg(nullptr)
	, _buttonOn(nullptr)
	, _buttonOff(nullptr)
	, _nextButtonPos(0.0f, 200.0f)
	, _titlePos(0.0f, 300.0f)
	, _bgPos(0.0f, 250.0f)
	, _state(Active)
{
	// TODO

}

UIScreen::~UIScreen()
{
	if (_title)
	{
		_title->unload();
		delete _title;
	}

	for (auto& btn : _buttons)
	{
		delete btn;
	}
	_buttons.clear();
}

void UIScreen::update(float deltaTime)
{

}

void UIScreen::draw(Shader *shader)
{
	if (_bg)
	{
		drawTexture(shader, _bg, _bgPos);
	}

	if (_title)
	{
		drawTexture(shader, _title, _titlePos);
	}

	for (auto& btn : _buttons)
	{
		Texture *tex = btn->getHighLighted() ? _buttonOn : _buttonOff;
		drawTexture(shader, tex, btn->getPosition());
		// draw button name
		drawTexture(shader, btn->getNameTexture(), btn->getPosition());
	}
}

void UIScreen::processInput(const unsigned char* keyState)
{
	if (!_buttons.empty())
	{
		// TODO
	}
}

void UIScreen::handleKeyPress(int key)
{
	switch (key)
	{
	case SDL_BUTTON_LEFT:
	{
		if (!_buttons.empty())
		{
			for (auto btn : _buttons)
			{
				if (btn->getHighLighted())
				{
					btn->onClick();
					break;
				}
			}
		}
	}
	default:
		break;
	}
}

void UIScreen::close()
{
	setState(Closing);
}

void UIScreen::setState(UIState state)
{
	_state = state;
}

UIScreen::UIState UIScreen::getState() const
{
	return _state;
}

void UIScreen::addButton(const std::string& name, std::function<void()> onClick)
{
	Vector2 dims(static_cast<float>(_buttonOn->getWidth()), static_cast<float>(_buttonOn->getHeight()));
	Button* b = new Button(name, _font, onClick, _nextButtonPos, dims);
	_buttons.emplace_back(b);

	// Update position of next button
	// Move down by height of button plus padding
	_nextButtonPos.y -= _buttonOff->getHeight() + 20.0f;
}

void UIScreen::drawTexture(Shader *shader, Texture *texture, const Vector2& offset, float scale)
{
	// Scale the quad by the width/height of texture
	Matrix4 scaleMat = Matrix4::createScale(
		static_cast<float>(texture->getWidth()) * scale,
		static_cast<float>(texture->getHeight()) * scale,
		1.0f);
	// Translate to position on screen
	Matrix4 transMat = Matrix4::createTranslation(
		Vector3(offset.x, offset.y, 0.0f));
	// Set world transform
	Matrix4 world = scaleMat * transMat;
	shader->setMatrixUniform("uWorldTransform", world);
	// Set current texture
	texture->setActive();
	// Draw quad
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

ENGINE_NAMESPACE_END