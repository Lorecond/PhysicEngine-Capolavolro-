#include "PhysicEngine/Core/Math/LinearAlgebra.h"

namespace PhysicEngine {

	PHYSIC_ENGINE_API float VectorLength(const Vector2f& vector)
	{
		return  std::sqrt(vector.X * vector.X + vector.Y * vector.Y);
	}

	PHYSIC_ENGINE_API const Vector2f& NormalizeVector(const Vector2f& vector)
	{
		float lenght = VectorLength(vector);
		return lenght > 0 ? vector / lenght : vector;
	}

	PHYSIC_ENGINE_API const float& DotProduct(const Vector2f& vector, const Vector2f& point)
	{
		return vector.X * point.X + vector.Y * point.Y;
	}

	PHYSIC_ENGINE_API const float CrossProduct(const Vector2f& a, const Vector2f& b)
	{
		return a.X * b.Y - a.Y * b.X;
	}

	PHYSIC_ENGINE_API void PointSegmentDistance(Vector2f p, Vector2f a, Vector2f b, float& distanceSquared, Vector2f& cp)
	{
		Vector2f ab = b - a;
		Vector2f ap = p - a;

		float proj = DotProduct(ap, ab);
		float abLenSq = ab.X * ab.X + ab.Y * ab.Y;
		float d = proj / abLenSq;

		if (d <= 0.f)
		{
			cp = a;
		}
		else if (d >= 1.f)
		{
			cp = b;
		}
		else
		{
			cp = a + ab * d;
		}

		float dx = p.X - cp.X;
		float dy = p.Y - cp.Y;

		distanceSquared = dx * dx + dy * dy;
	}

	PHYSIC_ENGINE_API bool NearlyEqual(const float& valueA, const float& valueB)
	{
		return (std::abs(valueA - valueB) < 0.0005f);
	}
	PHYSIC_ENGINE_API bool NearlyEqual(const Vector2f& valueA, const Vector2f& valueB)
	{
		return NearlyEqual(valueA.X, valueB.X) && NearlyEqual(valueA.Y, valueB.Y);
	}

}