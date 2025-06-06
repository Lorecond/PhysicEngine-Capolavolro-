#pragma once

#include "PhysicEngine/Core/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace PhysicEngine {

	class PHYSIC_ENGINE_API Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define PE_CORE_TRACE(...)    ::PhysicEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PE_CORE_INFO(...)     ::PhysicEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PE_CORE_WARN(...)     ::PhysicEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PE_CORE_ERROR(...)    ::PhysicEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PE_CORE_CRITICAL(...) ::PhysicEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define PE_TRACE(...)         ::PhysicEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PE_INFO(...)          ::PhysicEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define PE_WARN(...)          ::PhysicEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PE_ERROR(...)         ::PhysicEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define PE_CRITICAL(...)      ::PhysicEngine::Log::GetClientLogger()->critical(__VA_ARGS__)