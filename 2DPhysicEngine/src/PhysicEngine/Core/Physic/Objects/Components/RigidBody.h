#pragma once

#include "Component.h"

#include <SFML/Graphics.hpp>

#define GRAVITY Vector2f(0.f, 98.1f)

namespace PhysicEngine {

	struct BodyMaterial
	{
	public:
		BodyMaterial(const float& density = 1.f, const float& restitution = 0.5f,
			const float& staticFriction = 0.6f, const float& dynamicFriction = 0.6f)
			: Density(density), Restitution(restitution), StaticFriction(staticFriction), DynamicFriction(dynamicFriction){}
	public:
		float Density;
		float Restitution;
		float StaticFriction;
		float DynamicFriction;
	};

	enum class RigidBodyState
	{
		Movable = 0,
		Static
	};

	struct PHYSIC_ENGINE_API RigidBody
		: public Component
	{
	public:
		RigidBody(const float& mass = 1.f, const BodyMaterial& material = BodyMaterial(), const RigidBodyState& state = RigidBodyState::Movable);

	public:
		Vector2f Force; 
		Vector2f Acceleration; 
		Vector2f Velocity;

		float Rotation;
		float AngularAcceleration;
		float AngularVelocity;

		float Mass;
		float InvMass;
		
		float Inertia;
		float InvInertia;

		BodyMaterial Material;
		
		RigidBodyState State;
			
	public:
		void OnUpdate(const float& deltaTime);
		void RenderDebug(sf::RenderWindow& renderWindow, const sf::Color& color = sf::Color::Red);

	public: 
		void ApplyForce(const Vector2f& force);
		void SetStatus(const RigidBodyState& state);

	private:
		void SetInverse(const int& inv = 1);
	};

}