#pragma once

#include "PhysicEngine/Core/Core.h"

#include "PhysicEngine/Core/Math/Vectors.h"

namespace PhysicEngine {

	PHYSIC_ENGINE_API float VectorLength(const Vector2f& vector);

	PHYSIC_ENGINE_API const Vector2f& NormalizeVector(const Vector2f& vector);

	PHYSIC_ENGINE_API const float& DotProduct(const Vector2f& point, const Vector2f& vector);

	PHYSIC_ENGINE_API const float CrossProduct(const Vector2f& a, const Vector2f& b);

	PHYSIC_ENGINE_API void PointSegmentDistance(Vector2f p, Vector2f a, Vector2f b, float& distanceSquared, Vector2f& cp);


	PHYSIC_ENGINE_API bool NearlyEqual(const float& valueA, const float& valueB);
	PHYSIC_ENGINE_API bool NearlyEqual(const Vector2f& valueA, const Vector2f& valueB);

}