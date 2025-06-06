#pragma once

#include <SFML/Graphics.hpp>

struct WindowData
{
	sf::VideoMode VideoMode;
	std::string Title;
	sf::Uint32 Style;
	sf::ContextSettings ContextSettings;

	WindowData(
		const sf::VideoMode& videoMode = sf::VideoMode(960, 540),
		const std::string& title = "Test",
		const sf::Uint32& style = sf::Style::Default,
		const sf::ContextSettings settings = sf::ContextSettings()
	) : VideoMode(videoMode), Title(title), Style(style), ContextSettings(settings) {
	}
};

class Window
{
public:
	Window(const WindowData& data = WindowData());
	~Window();

public: // Application loop
	bool Running();
	bool PollEvent();
	void HandleEvent();
	void Update();
	void Clear(const sf::Color& color = sf::Color::Black);
	void Display();

public: // Set
	void SetView(sf::View& view);

public: // Get
	sf::RenderWindow& GetWindow() { return this->m_Window; }
	sf::Event& GetEvent() { return this->m_Event; }
	float& GetDeltaTime() { return this->m_DeltaTime; }

private: // Window
	void Init(const WindowData& data);
	void Shutdown();

private:
	sf::RenderWindow m_Window;
	sf::Event m_Event;
	WindowData m_Data;
	sf::Clock m_Clock;
	float m_DeltaTime;
};