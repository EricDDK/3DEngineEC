#include "CameraComponent.h"

ENGINE_NAMESPACE_START

CameraComponent::CameraComponent(GameObject *gameObject, int order)
	:Component(gameObject, order)
{

}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::setViewMatrix(const Matrix4& view)
{
	// TODO
	// Pass view matrix to renderer

}

ENGINE_NAMESPACE_END