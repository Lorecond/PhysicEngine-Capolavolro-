#pragma once

#include "PhysicEngine/Core/Physic/Objects/Components.h"

namespace PhysicEngine {

	class PHYSIC_ENGINE_API Object
	{
	public:
		Object(BoxCollider& collider = BoxCollider(), RigidBody& body = RigidBody());
		~Object() = default;

	public: 
		void OnUpdate(const float& deltaTime);
		void OnRender(sf::RenderWindow& renderWindow);

	public: // Set
		void Move(const Vector2f& offset);
		void SetPosition(const Vector2f& position);
		void AddRotation(const float& radians);
		void SetRotation(const float& radians);

	public: // Components
		BoxCollider Collider;
		RigidBody Body;
	};

}