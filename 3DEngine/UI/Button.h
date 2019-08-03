#ifndef _UI_BUTTON_H__
#define _UI_BUTTON_H__

#include "../Common/Macro.h"
#include <string>
#include <functional>
#include "../Math/Math.h"

ENGINE_NAMESPACE_START

class Shader;
class Texture;
class Font;

class Button
{
public:

	Button(const std::string& name, Font *font, std::function<void()> onClick, const Vector2& pos, const Vector2& dims);

	~Button();

	void setName(const std::string& name);

	Texture *getNameTexture() const;

	const Vector2& getPosition() const;

	void setPosition(const Vector2& position);

	void setHighLighted(bool shl);

	bool getHighLighted() const;

	bool contains(const Vector2& point) const;

	void onClick();

private:

	std::function<void()> _onClick;

	std::string _name;

	Texture *_nameTexture;

	Font *_font;

	Vector2 _position;

	// rect
	Vector2 _dimension;

	bool _highLighted;

};

ENGINE_NAMESPACE_END

#endif