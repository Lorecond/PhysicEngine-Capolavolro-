#include "PhysicEngine/Core/Math/Geometry.h"

namespace PhysicEngine {

	PHYSIC_ENGINE_API const double& PointsDistance(const Vector2f& pointA, const Vector2f& pointB)
	{
		return std::abs(std::sqrt(std::pow((pointA.X - pointB.X), 2) + std::pow((pointA.Y - pointB.Y), 2)));
	}

	PHYSIC_ENGINE_API const Vector2f& ArithmeticMean(const std::vector<Vector2f>& points)
	{
		float sumX = 0.f;
		float sumY = 0.f;

		for (const auto& point : points) {
			sumX += point.X;
			sumY += point.Y;
		}

		return Vector2f(sumX / points.size(), sumY / points.size());
	}

}