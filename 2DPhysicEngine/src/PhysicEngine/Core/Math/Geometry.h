#pragma once

#include "PhysicEngine/Core/Core.h"

#include "PhysicEngine/Core/Math/Vectors.h"
#include <vector>

namespace PhysicEngine {

	PHYSIC_ENGINE_API const double& PointsDistance(const Vector2f& pointA, const Vector2f& pointB);

	PHYSIC_ENGINE_API const Vector2f& ArithmeticMean(const std::vector<Vector2f>& points);

}