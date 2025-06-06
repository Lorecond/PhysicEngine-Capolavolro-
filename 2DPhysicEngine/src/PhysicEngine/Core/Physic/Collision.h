#pragma once

#include "PhysicEngine/Core/Core.h"

#include "PhysicEngine/Core/Physic/Objects/Object.h"

namespace PhysicEngine {

	struct PHYSIC_ENGINE_API ManiFold
	{
	public:
		Object* ObjectA;
		Object* ObjectB;
		Vector2f Normal;
		float Depth;
		Vector2f ContactPointA;
		Vector2f ContactPointB;
		int ContactCount;

	public:
		ManiFold
		(
			Object* objectA, Object* objectB,
			const Vector2f& normal = Vector2f(), const float& depth = 0.f,
			const Vector2f& contactPointA = Vector2f(), const Vector2f& contactPointB = Vector2f(), const int& contactCount = 0
		)
			: ObjectA(objectA), ObjectB(objectB),
			Normal(normal), Depth(depth),
			ContactPointA(contactPointA), ContactPointB(contactPointB), ContactCount(contactCount) {
		}
	};

	bool AABB(ManiFold& maniFold);

	// -- SAT --
	bool SAT(ManiFold& maniFold);
	void FindContactPoint(const std::vector<Vector2f>& verticesA, const std::vector<Vector2f>& verticesB, ManiFold& maniFold);
	const Vector2f& GetAxis(const Vector2f& axisA, const Vector2f& axisB);
	void projectPoint(const Vector2f& axis, const std::vector<Vector2f>& vertices, float& min, float& max);
}