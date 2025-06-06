#include "Application.h"

#ifdef EN_PLATFORM_WINDOWS

int main()
{
	PhysicEngine::Log::Init();

	auto App = CreateApplication();

	App->Run();

	delete App;
}

#endif