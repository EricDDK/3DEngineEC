#ifndef _GAMEOBJECT_PLANEGAMEOBJECT_H__
#define _GAMEOBJECT_PLANEGAMEOBJECT_H__

#include "../Common/Macro.h"
#include "GameObject.h"

ENGINE_NAMESPACE_START

class BoxComponent;
class Game;

class PlaneGameObject : public GameObject
{
public:

	PlaneGameObject(Game* game);

	~PlaneGameObject();

	BoxComponent* getBox();

private:

	BoxComponent* _box;

};

ENGINE_NAMESPACE_END

#endif