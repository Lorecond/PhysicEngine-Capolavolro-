#pragma once

#include "PhysicEngine/Core/Core.h"
#include "PhysicEngine/Core/Math.h"

namespace PhysicEngine {

	struct PHYSIC_ENGINE_API Component
	{
	public:
		Component(const Vector2f& position = Vector2f()) : Position(position) {}

	public:
		Vector2f Position;

	public: 
		void Move(const Vector2f& offset);
	};

}