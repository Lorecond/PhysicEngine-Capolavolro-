#pragma once

#include "PhysicEngine/Core/Core.h"

namespace PhysicEngine {

	PHYSIC_ENGINE_API constexpr float DegreesToRadians(const float& degrees);

	PHYSIC_ENGINE_API constexpr float RadiansToDegrees(const float& radians);

	PHYSIC_ENGINE_API const double& Sin(const float& radians);
	PHYSIC_ENGINE_API const double& Arcsin(const float& radians);
	PHYSIC_ENGINE_API const double& Cos(const float& radians);
	PHYSIC_ENGINE_API const double& Arccos(const float& radians);
	PHYSIC_ENGINE_API const double& Tan(const float& radians);
	PHYSIC_ENGINE_API const double& Arctan(const float& radians);

}