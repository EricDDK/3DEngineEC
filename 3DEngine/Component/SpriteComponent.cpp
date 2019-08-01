#include "SpriteComponent.h"
#include "../Render/Shader.h"
#include "../Math/Matrix4.h"

ENGINE_NAMESPACE_START

// TODO Sprite
SpriteComponent::SpriteComponent()
{

}

// TODO Sprite
SpriteComponent::SpriteComponent(GameObject *gameObject, int order)
	: Component(gameObject, order)
	, _texture(nullptr)
	, _texWidth(0)
	, _texHeight(0)
	, _isVisible(false)
{

}

SpriteComponent::~SpriteComponent()
{
	// TODO

}

void SpriteComponent::draw(Shader *shader)
{
	if (_texture)
	{
		Matrix4 scaleMat4 = Matrix4::createScale(static_cast<float>(_texWidth), static_cast<float>(_texHeight), 1.0f);

		Matrix4 world = scaleMat4 * _gameObject->getWorldTransform();

		// set world transform
		shader->setMatrixUniform("uWorldTransform", world);

		_texture->setActive();
		// draw quad
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	}
}

void SpriteComponent::setTexture(Texture *texture)
{
	_texture = texture;
	_texWidth = texture->getWidth();
	_texHeight = texture->getHeight();
}

void SpriteComponent::setVisible(bool isVisible)
{
	_isVisible = isVisible;
}

bool SpriteComponent::isVisible() const
{
	return _isVisible;
}

ENGINE_NAMESPACE_END