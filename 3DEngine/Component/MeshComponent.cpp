#include "MeshComponent.h"
#include "../Common/Mesh.h"
#include "../GameObject/GameObject.h"
#include "../Render/Shader.h"
#include "../Render/Texture.h"
#include "../Render/VertexArray.h"

ENGINE_NAMESPACE_START

MeshComponent::MeshComponent(GameObject* gameObject, bool isSkeletal)
	: Component(gameObject)
	, _mesh(nullptr)
	, _textureIndex(0)
	, _isVisible(true)
	, _isSkeletal(isSkeletal)
{
	// TODO

}

MeshComponent::~MeshComponent()
{
	// TODO

}

void MeshComponent::draw(Shader* shader)
{
	if (_mesh)
	{
		// Set the world transform
		shader->setMatrixUniform("uWorldTransform", _gameObject->getWorldTransform());
		// Set specular power
		shader->setFloatUniform("uSpecPower", _mesh->getSpecPower());
		// Set the active texture
		Texture* t = _mesh->getTexture(_textureIndex);
		if (t)
		{
			t->setActive();
		}
		// Set the mesh's vertex array as active
		VertexArray* va = _mesh->getVertexArray();
		va->setActive();
		// Draw
		glDrawElements(GL_TRIANGLES, va->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}
}

void MeshComponent::setMesh(Mesh* mesh)
{
	_mesh = mesh;
}

void MeshComponent::setTextureIndex(size_t index)
{
	_textureIndex = index;
}

void MeshComponent::setVisible(bool visible)
{
	_isVisible = visible;
}

bool MeshComponent::getVisible() const
{
	return _isVisible;
}

bool MeshComponent::getIsSkeletal() const
{
	return _isSkeletal;
}

ENGINE_NAMESPACE_END