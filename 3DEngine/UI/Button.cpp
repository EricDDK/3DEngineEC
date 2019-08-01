#include "Button.h"
#include "../Render/Shader.h"
#include "../Render/Texture.h"
#include "Font.h"

ENGINE_NAMESPACE_START

Button::Button(const std::string& name, Font *font, std::function<void()> onClick, const Vector2& pos, const Vector2& dims)
	: _name(name)
	, _onClick(onClick)
	, _font(font)
	, _nameTexture(nullptr)
	, _position(pos)
	, _dimension(dims)
	, _highLighted(false)
{

}

Button::~Button()
{
	if (_nameTexture)
	{
		_nameTexture->unload();
		delete _nameTexture;
	}
}

void Button::setName(const std::string& name)
{
	_name = name;
}

Texture * Button::getNameTexture() const
{
	return _nameTexture;
}

const Vector2& Button::getPosition() const
{
	return _position;
}

void Button::setPosition(const Vector2& position)
{
	_position = position;
}

void Button::setHighLighted(bool shl)
{
	_highLighted = shl;
}

bool Button::getHighLighted() const
{
	return _highLighted;
}

bool Button::contains(const Vector2& point) const
{
	bool no = point.x < (_position.x - _dimension.x / 2.0f) ||
		point.x >(_position.x + _dimension.x / 2.0f) ||
		point.y < (_position.y - _dimension.y / 2.0f) ||
		point.y >(_position.y + _dimension.y / 2.0f);
	return !no;
}

void Button::onClick()
{
	// called call back function.
	if (_onClick)
	{
		_onClick();
	}
}

ENGINE_NAMESPACE_END