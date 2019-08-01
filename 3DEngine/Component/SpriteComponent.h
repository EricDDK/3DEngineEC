#ifndef _COMPONENT_SPRITECOMPONENT_H__
#define _COMPONENT_SPRITECOMPONENT_H__

#include "../Common/Macro.h"
#include "Component.h"
#include "../Render/Texture.h"
#include "../Render/VertexArray.h"

ENGINE_NAMESPACE_START

class Shader;

class SpriteComponent : public Component
{
public:

	SpriteComponent();

	SpriteComponent(GameObject *gameObject, int order = 0);

	~SpriteComponent();

	virtual void draw(Shader *shader);

	virtual void setTexture(Texture *texture);

	void setVisible(bool isVisible);

	bool isVisible() const;

protected:

	Texture *_texture;

	int _texWidth;

	int _texHeight;

	bool _isVisible;

};

ENGINE_NAMESPACE_END

#endif