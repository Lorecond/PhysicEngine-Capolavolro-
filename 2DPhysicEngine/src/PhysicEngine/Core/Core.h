#pragma once

#include <memory>

#ifdef EN_PLATFORM_WINDOWS
	#ifdef EN_BUILD_DLL	
		#define PHYSIC_ENGINE_API __declspec(dllexport)
	#else 
		#define PHYSIC_ENGINE_API __declspec(dllimport)
	#endif 
#else
	#error This physic engine support only Windows
#endif

namespace PhysicEngine {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

#include "PhysicEngine/Core/Log.h"