#include "PhysicWorld.h"

namespace PhysicEngine {

	PhysicWorld::PhysicWorld()
	{
		PE_CORE_INFO("Physic world initialized");
	}
	PhysicWorld::~PhysicWorld()
	{
		DeleteObjects();
	}

	// Application loop
	void PhysicWorld::OnEvent(sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				m_IsRunning = !m_IsRunning;
				PE_CORE_INFO("Simulation status : {0}", m_IsRunning);
			}

			if (event.key.code == sf::Keyboard::N)
			{
				m_NextStep = true;
				PE_CORE_INFO("Next Step");
			}
			if (event.key.code == sf::Keyboard::B)
			{
				if (m_OldStep.empty())
					PE_CORE_WARN("Vector m_OldStep is empty!");
				else
				{
					OldStep oldStep = m_OldStep[m_OldStep.size() - 1];

					oldStep.ObjectA->Body.Velocity = oldStep.VelocityA;
					oldStep.ObjectB->Body.Velocity = oldStep.VelocityB;
					oldStep.ObjectA->SetPosition(oldStep.PositionA);
					oldStep.ObjectB->SetPosition(oldStep.PositionB);

					oldStep.ObjectA->Body.AngularVelocity = oldStep.AngularVelocityA;
					oldStep.ObjectB->Body.AngularVelocity = oldStep.AngularVelocityB;
					oldStep.ObjectA->SetRotation(oldStep.RotationA);
					oldStep.ObjectB->SetRotation(oldStep.RotationB);

					m_OldStep.resize(m_OldStep.size() - 1);

					PE_CORE_INFO("Back Step");
				}
			}
		}
	}
	void PhysicWorld::OnUpdate(const float& deltaTime)
	{
		if (!m_IsRunning && !m_NextStep)
			return;

		float time = deltaTime / m_Iterations;
		for (int i = 0; i < m_Iterations; i++)
		{
			UpdateObject(time);
			UpdateCollision();
			ResolveCollision();
		}

		m_NextStep = false;
	}
	void PhysicWorld::OnRender(sf::RenderWindow& renderWindow)
	{
		RenderDebug(renderWindow);
	}

	void PhysicWorld::AddObject(Object* object)
	{
		m_Objects.push_back(object);
		PE_CORE_INFO("Ci  sono {0} oggetti nella simulazione.", m_Objects.size());
	}
	void PhysicWorld::DeleteObjects()
	{
		for (auto& object : m_Objects)
		{
			delete object;
		}
		m_Objects.clear();
		PE_CORE_INFO("Oggetti eliminati.");
	}

	std::vector<Object*>& PhysicWorld::GetObjectList()
	{
		return m_Objects;
	}

	void PhysicWorld::RenderDebug(sf::RenderWindow& renderWindow)
	{
		for (auto& object : m_Objects)
		{
			object->Collider.RenderDebug(renderWindow);
			object->Body.RenderDebug(renderWindow);
		}

		sf::VertexArray contactList(sf::Points, m_ContactListDebug.size());
		for (int i = 0; i < contactList.getVertexCount(); i++)
		{
			contactList[i].color = sf::Color::Green;
			contactList[i].position = sf::Vector2f(m_ContactListDebug[i].X, m_ContactListDebug[i].Y);
		}
		renderWindow.draw(contactList);
		if (m_IsRunning)
			m_ContactListDebug.clear();
	}

	void PhysicWorld::UpdateObject(const float& deltaTime)
	{
		for (auto& object : m_Objects)
		{
			object->OnUpdate(deltaTime);
		}
	}
	void PhysicWorld::UpdateCollision()
	{
		if (m_Objects.size() == 0)
			return;

		sf::Clock clock;
		for (std::size_t i = 0; i < m_Objects.size() - 1; i++)
		{
			for (std::size_t j = i + 1; j < m_Objects.size(); j++)
			{
				clock.restart();

				ManiFold maniFold(m_Objects[i], m_Objects[j]);
				
				if (maniFold.ObjectA->Body.State == RigidBodyState::Static && maniFold.ObjectB->Body.State == RigidBodyState::Static)
					continue;

				if (SAT(maniFold))
				{
					m_ManiFold.push_back(maniFold);
				}
			}
		}
	}
	void PhysicWorld::ResolveCollision()
	{
		sf::Clock clock;
		for (auto& collision : m_ManiFold)
		{
			// --- Debug ---
			OldStep oldStep;
			oldStep.ObjectA = collision.ObjectA;
			oldStep.ObjectB = collision.ObjectB;

			oldStep.VelocityA = collision.ObjectA->Body.Velocity;
			oldStep.VelocityB = collision.ObjectB->Body.Velocity;
			oldStep.PositionA = collision.ObjectA->Body.Position;
			oldStep.PositionB = collision.ObjectB->Body.Position;

			oldStep.AngularVelocityA = collision.ObjectA->Body.AngularVelocity;
			oldStep.AngularVelocityB = collision.ObjectB->Body.AngularVelocity;
			oldStep.RotationA = collision.ObjectA->Body.Rotation;
			oldStep.RotationB = collision.ObjectB->Body.Rotation;

			if (m_OldStep.size() >= 50)
				m_OldStep.erase(m_OldStep.begin()); 

			m_OldStep.push_back(oldStep);

			m_ContactListDebug.push_back(collision.ContactPointA);
			if (collision.ContactCount == 2)
				m_ContactListDebug.push_back(collision.ContactPointB);
			// --- ----- ---

			clock.restart();

			Object& objA = *collision.ObjectA;
			Object& objB = *collision.ObjectB;

			if (objB.Body.State == RigidBodyState::Static)
				objA.Move(-collision.Normal * collision.Depth);
			else if (objA.Body.State == RigidBodyState::Static)
				objB.Move(collision.Normal * collision.Depth);
			else {
				Vector2f offSet = collision.Normal * collision.Depth / 2.f;
				objA.Move(-offSet);
				objB.Move(offSet);
			}

			ApplyRotation(collision);
			ApplyFriction(collision);
		}
		m_ManiFold.clear();
	}

	void PhysicWorld::ApplyFriction(ManiFold& maniFold)
	{
		Object& objA = *maniFold.ObjectA;
		Object& objB = *maniFold.ObjectB;

		float frictionCoefficient = std::max(objA.Body.Material.DynamicFriction, objB.Body.Material.DynamicFriction);

		float na = GRAVITY.Y * objA.Body.Mass;
		float fa = na * frictionCoefficient;
		objA.Body.ApplyForce(Vector2f(-NormalizeVector(objA.Body.Velocity).X * fa, 0.f));

		float nb = GRAVITY.Y * objB.Body.Mass;
		float fb = nb * frictionCoefficient;
		objB.Body.ApplyForce(Vector2f(-NormalizeVector(objB.Body.Velocity).X * fb, 0.f));
	}
	void PhysicWorld::ApplyRotation(ManiFold& maniFold)
	{
		Object& objA = *maniFold.ObjectA;
		Object& objB = *maniFold.ObjectB;
		Vector2f normal = maniFold.Normal;
		Vector2f contactA = maniFold.ContactPointA;
		Vector2f contactB = maniFold.ContactPointB;
		int contactCount = maniFold.ContactCount;

		float e = std::min(objA.Body.Material.Restitution, objB.Body.Material.Restitution);

		Vector2f contactList[2];
		contactList[0] = contactA;
		contactList[1] = contactB;

		Vector2f impulseList[2];
		Vector2f raList[2];
		Vector2f rbList[2];

		for (int i = 0; i < contactCount; i++)
		{
			impulseList[i] = Vector2f();
			raList[i] = Vector2f();
			rbList[i] = Vector2f();
		}

		for (int i = 0; i < contactCount; i++)
		{
			Vector2f ra = contactList[i] - objA.Body.Position;
			Vector2f rb = contactList[i] - objB.Body.Position;

			raList[i] = ra;
			rbList[i] = rb;

			Vector2f raPerp = Vector2f(-ra.Y, ra.X);
			Vector2f rbPerp = Vector2f(-rb.Y, rb.X);

			Vector2f angularLinearVelocityA = raPerp * objA.Body.AngularVelocity;
			Vector2f angularLinearVelocityB = rbPerp * objB.Body.AngularVelocity;

			Vector2f relativeVelocity = 
				(objB.Body.Velocity + angularLinearVelocityB) -
				(objA.Body.Velocity + angularLinearVelocityA);
			float contactVelocityMag = DotProduct(relativeVelocity, normal);

			if (contactVelocityMag > 0.f)
				continue;

			float raPerpDotN = DotProduct(raPerp, normal);
			float rbPerpDotN = DotProduct(rbPerp, normal);

			float denom = objA.Body.InvMass + objB.Body.InvMass +
				(raPerpDotN * raPerpDotN) * objA.Body.InvInertia +
				(rbPerpDotN * rbPerpDotN) * objB.Body.InvInertia;

			float j = -(1.f + e) * contactVelocityMag;
			j /= denom;
			j /= (float)contactCount;

			Vector2f impulse = normal * j;

			impulseList[i] = impulse;
		}

		for (int i = 0; i < contactCount; i++)
		{
			Vector2f impulse = impulseList[i];
			Vector2f ra = raList[i];
			Vector2f rb = rbList[i];

			objA.Body.Velocity += -impulse * objA.Body.InvMass;
			objA.Body.AngularVelocity += -CrossProduct(ra, impulse) * objA.Body.InvInertia;
			objB.Body.Velocity += impulse * objB.Body.InvMass;
			objB.Body.AngularVelocity += CrossProduct(rb, impulse) * objB.Body.InvInertia;
		}
	}
	void PhysicWorld::ApplyImpulse(ManiFold& maniFold)
	{
		Object& objA = *maniFold.ObjectA;
		Object& objB = *maniFold.ObjectB;

		Vector2f relativeVelocity = objB.Body.Velocity - objA.Body.Velocity;

		float e = std::min(objA.Body.Material.Restitution, objB.Body.Material.Restitution);
		float j = -(1.f + e) * DotProduct(relativeVelocity, maniFold.Normal);
		j /= objA.Body.InvMass + objB.Body.InvMass;

		objA.Body.Velocity -= (maniFold.Normal * j) * objA.Body.InvMass;
		objB.Body.Velocity += (maniFold.Normal * j) * objB.Body.InvMass;
	}
}