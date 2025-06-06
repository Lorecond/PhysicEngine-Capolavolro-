#include "PhysicEngine/Core/Math/Goniometry.h"

namespace PhysicEngine {

	PHYSIC_ENGINE_API constexpr float DegreesToRadians(const float& degrees)
	{
		return degrees * 0.0174533f;
	}

	PHYSIC_ENGINE_API constexpr float RadiansToDegrees(const float& radians)
	{
		return radians * 57.2958f;
	}

	PHYSIC_ENGINE_API const double& Sin(const float& radians)
	{
		return std::sin(radians);
	}
	PHYSIC_ENGINE_API const double& Arcsin(const float& radians)
	{
		return std::asin(radians);
	}
	PHYSIC_ENGINE_API const double& Cos(const float& radians)
	{
		return std::cos(radians);
	}
	PHYSIC_ENGINE_API const double& Arccos(const float& radians)
	{
		return std::acos(radians);
	}
	PHYSIC_ENGINE_API const double& Tan(const float& radians)
	{
		return std::tan(radians);
	}
	PHYSIC_ENGINE_API const double& Arctan(const float& radians)
	{
		return std::atan(radians);
	}

}