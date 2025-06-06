#include "Object.h"

namespace PhysicEngine {


	Object::Object(BoxCollider& collider, RigidBody& body)
		: Collider(collider), Body(body)
	{
	}

	void Object::OnUpdate(const float& deltaTime)
	{
		Body.OnUpdate(deltaTime); // Aggiorna la posizione del corpo

		SetPosition(Body.Position); // Imposta la posizione degli altri componenti 
		SetRotation(Body.Rotation); // Imposta la Rotazione degli altri componenti
	}
	void Object::OnRender(sf::RenderWindow& renderWindow)
	{
	
	}

	// Set
	void Object::Move(const Vector2f& offset)
	{
		Collider.Move(offset);
		Body.Move(offset);
	}
	void Object::SetPosition(const Vector2f& position)
	{
		Collider.Position = position;
		Body.Position = position;
	}
	void Object::AddRotation(const float& radians)
	{
		Collider.Rotation += radians;
		Body.Rotation += radians;
	}
	void Object::SetRotation(const float& radians)
	{
		Collider.Rotation = radians;
		Body.Rotation = radians;
	}

}