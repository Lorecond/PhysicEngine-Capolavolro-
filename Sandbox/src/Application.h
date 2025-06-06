#pragma once

#include <PhysicEngine.h>

#include "Window.h"

using namespace PhysicEngine;

class Application
{
public:
	Application();
	virtual ~Application();

public: // Application loop
	void Event();
	void Update();
	void Render();

public:
	void Run();
	void Close();
	
private:
	bool m_Running = true;
	Window m_Window;
	sf::View view;
	void UpdateView();

	sf::Vector2f MousePos;
	sf::Vector2f oldPos;
	Object* objToMove = nullptr;

	PhysicWorld physicWorld;
};

Application* CreateApplication();