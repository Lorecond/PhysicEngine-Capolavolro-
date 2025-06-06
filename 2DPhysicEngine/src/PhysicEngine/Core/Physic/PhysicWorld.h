#pragma once

#include "PhysicEngine/Core/Core.h"

#include "PhysicEngine/Core/Physic/Collision.h"

namespace PhysicEngine {

	struct OldStep
	{
	public:
		Object* ObjectA;
		Object* ObjectB;

		Vector2f VelocityA;
		Vector2f VelocityB;
		Vector2f PositionA;
		Vector2f PositionB;

		float AngularVelocityA;
		float AngularVelocityB;
		float RotationA;
		float RotationB;
	};


	class PHYSIC_ENGINE_API PhysicWorld
	{
	public:
		PhysicWorld();
		~PhysicWorld();

	public:
		void OnEvent(sf::Event& event);
		void OnUpdate(const float& deltaTime);
		void OnRender(sf::RenderWindow& renderWindow);

	public:
		void AddObject(Object* object);
		void DeleteObjects();

		std::vector<Object*>& GetObjectList();
		
	private:
		bool m_IsRunning = false;
		bool m_NextStep = false;
		int m_Iterations = 5;

	private: // Debug
		void RenderDebug(sf::RenderWindow& renderWindow);
		std::vector<Vector2f> m_ContactListDebug;

	private:
		std::vector<Object*> m_Objects;
		std::vector<ManiFold> m_ManiFold;
		std::vector<OldStep> m_OldStep;

		void UpdateObject(const float& deltaTime);
		void UpdateCollision();
		void ResolveCollision();

		void ApplyFriction(ManiFold& maniFold);
		void ApplyRotation(ManiFold& maniFold);
		void ApplyImpulse(ManiFold& maniFold);
	};

}