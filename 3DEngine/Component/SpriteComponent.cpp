#include "SpriteComponent.h"

ENGINE_NAMESPACE_START

// TODO Sprite
SpriteComponent::SpriteComponent()
{

}

SpriteComponent::SpriteComponent(GameObject *gameObject, int order)
{

}

SpriteComponent::~SpriteComponent()
{

}

void SpriteComponent::draw()
{

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