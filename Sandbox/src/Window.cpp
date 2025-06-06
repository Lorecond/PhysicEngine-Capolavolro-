#include "Window.h"

Window::Window(const WindowData& data)
{
	Init(data);
}
Window::~Window()
{
	Shutdown();
}

// Application loop
bool Window::Running()
{
	return this->m_Window.isOpen();
}
bool Window::PollEvent()
{
	return this->m_Window.pollEvent(this->m_Event);
}
void Window::HandleEvent()
{
	if (this->m_Event.type == sf::Event::Closed)
		this->Shutdown();
}
void Window::Update()
{
	this->m_DeltaTime = this->m_Clock.restart().asSeconds();
}
void Window::Clear(const sf::Color& color)
{
	this->m_Window.clear(color);
}
void Window::Display()
{
	this->m_Window.display();
}

// Set
void Window::SetView(sf::View& view)
{
	this->m_Window.setView(view);
}

// Window
void Window::Init(const WindowData& data)
{
	this->m_Data.VideoMode = data.VideoMode;
	this->m_Data.Title = data.Title;
	this->m_Data.Style = data.Style;
	this->m_Data.ContextSettings = data.ContextSettings;
	this->m_DeltaTime = 0.f;

	this->m_Window.create(this->m_Data.VideoMode, this->m_Data.Title, this->m_Data.Style, this->m_Data.ContextSettings);

	this->m_Window.setVerticalSyncEnabled(true);

	this->m_Window.setFramerateLimit(120.f);
}
void Window::Shutdown()
{
	this->m_Window.close();
}