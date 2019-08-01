#ifndef _COMPONENT_MESHCOMPONENT_H__
#define _COMPONENT_MESHCOMPONENT_H__

#include "../Common/Macro.h"
#include "Component.h"

ENGINE_NAMESPACE_START

class GameObject;

class MeshComponent : public Component
{
public:

	MeshComponent(class GameObject* gameObject, bool isSkeletal = false);

	~MeshComponent();

	virtual void draw(class Shader* shader);

	virtual void setMesh(class Mesh* mesh);

	void setTextureIndex(size_t index);

	void setVisible(bool visible);

	bool getVisible() const;

	bool getIsSkeletal() const;

protected:

	class Mesh* _mesh;

	size_t _textureIndex;

	bool _isVisible;

	bool _isSkeletal;

};

ENGINE_NAMESPACE_END

#endif