#include "PlaneGameObject.h"
#include "../Component/BoxComponent.h"
#include "../Game.h"
#include "../Component/MeshComponent.h"
#include "../Component/BoxComponent.h"
#include "../Common/Mesh.h"

ENGINE_NAMESPACE_START

PlaneGameObject::PlaneGameObject(Game* game)
	: GameObject(game)
{
	setScale(10.0f);
	MeshComponent* mc = new MeshComponent(this);
	// TODO
	//Mesh* mesh = GetGame()->GetRenderer()->GetMesh("Assets/Plane.gpmesh");
}

PlaneGameObject::~PlaneGameObject()
{
	// TODO
}

BoxComponent* PlaneGameObject::getBox()
{
	return _box;
}

ENGINE_NAMESPACE_END