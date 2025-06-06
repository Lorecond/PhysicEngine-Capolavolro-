#include "Component.h"

namespace PhysicEngine {

	void Component::Move(const Vector2f& offset)
	{
		Position += offset;
	}

}