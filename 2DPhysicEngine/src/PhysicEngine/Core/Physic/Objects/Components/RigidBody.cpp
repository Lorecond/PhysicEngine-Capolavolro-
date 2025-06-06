#include "RigidBody.h"

namespace PhysicEngine {

	RigidBody::RigidBody(const float& mass, const BodyMaterial& material, const RigidBodyState& state) 
		: Mass(mass), Material(material), State(state)
	{
		Force = Vector2f();
		Acceleration = Vector2f(); 
		Velocity = Vector2f();

		Rotation = 0.f;
		AngularAcceleration = 0.f; 
		AngularVelocity = 0.f;

		Inertia = (1.f / 12.f) * Mass * (50.f * 50.f + 50.f * 50.f);

		SetStatus(State);
	}

	void RigidBody::OnUpdate(const float& deltaTime)
	{

		if (State == RigidBodyState::Static)
		{
			Velocity = Vector2f();
			AngularAcceleration = 0.f;
			AngularVelocity = 0.f;
			return;
		}

		Acceleration = Force / Mass;

		Velocity += GRAVITY * deltaTime;

		Velocity += Acceleration * deltaTime * 0.5f;
		Position += Velocity * deltaTime;
		Velocity += Acceleration * deltaTime * 0.5f;

		Force = Vector2f();

		AngularVelocity += AngularAcceleration * deltaTime;
		Rotation += AngularVelocity * deltaTime;
	}
	void RigidBody::RenderDebug(sf::RenderWindow& renderWindow, const sf::Color& color)
	{
		sf::VertexArray debug(sf::Points, 1);

		debug[0].color = color;
		debug[0].position = sf::Vector2f(Position.X, Position.Y);

		renderWindow.draw(debug);
	}

	void RigidBody::ApplyForce(const Vector2f& force)
	{
		Force += force;
	}
	void RigidBody::SetStatus(const RigidBodyState& state)
	{
		switch (state)
		{
		case RigidBodyState::Movable:
			SetInverse(1);
			break;
		case RigidBodyState::Static:
			SetInverse(0);
			break;

		default:
			SetInverse();
			break;
		}
	}

	void RigidBody::SetInverse(const int& inv)
	{
		InvMass = inv / Mass;
		InvInertia = inv / Inertia;
	}

}