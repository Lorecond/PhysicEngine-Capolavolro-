#include "Application.h"	

Application::Application()
{
	view.setSize(sf::Vector2f(960.f, 540.f));
	view.setCenter(sf::Vector2f(0.f, 0.f));

	Object* object = new Object(BoxCollider(Vector2f(50, 50)));
	physicWorld.AddObject(object);

	object = new Object(BoxCollider(Vector2f(2000, 100)), RigidBody(1.f, BodyMaterial(1.f, 1.f, 1.f, 1.f), RigidBodyState::Static));
	object->SetPosition(Vector2f(0, 200));
	physicWorld.AddObject(object);

	object = new Object(BoxCollider(Vector2f(400, 50)), RigidBody(1.f, BodyMaterial(1.f, 1.f, 0.4f, 0.4f), RigidBodyState::Static));
	object->SetPosition(Vector2f(-300, -200));
	object->SetRotation(DegreesToRadians(20));
	physicWorld.AddObject(object);

	object = new Object(BoxCollider(Vector2f(400, 50)), RigidBody(1.f, BodyMaterial(1.f, 1.f, 0.4f, 0.4f), RigidBodyState::Static));
	object->SetPosition(Vector2f(100, -450));
	object->SetRotation(DegreesToRadians(-30));
	physicWorld.AddObject(object);

	object = new Object(BoxCollider(Vector2f(1000, 50)), RigidBody(1.f, BodyMaterial(1.f, 1.f, 1.f, 1.f), RigidBodyState::Static));
	object->SetPosition(Vector2f(-1000, -100));
	object->SetRotation(DegreesToRadians(90));
	physicWorld.AddObject(object);

	object = new Object(BoxCollider(Vector2f(1000, 50)), RigidBody(1.f, BodyMaterial(1.f, 1.f, 1.f, 1.f), RigidBodyState::Static));
	object->SetPosition(Vector2f(1000, -100));
	object->SetRotation(DegreesToRadians(90));
	physicWorld.AddObject(object);

}
Application::~Application()
{
	
}

void Application::Event()
{
	while (m_Window.PollEvent())
	{
		m_Window.HandleEvent();
		physicWorld.OnEvent(m_Window.GetEvent());

		if (this->m_Window.GetEvent().type == sf::Event::MouseWheelScrolled)
		{
			if (this->m_Window.GetEvent().mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
				view.zoom((this->m_Window.GetEvent().mouseWheelScroll.delta > 0) ? 0.9f : 1.1f);
				this->m_Window.SetView(view);
			}
		}

		if (m_Window.GetEvent().type == sf::Event::MouseButtonPressed)
		{
			if (m_Window.GetEvent().mouseButton.button == sf::Mouse::Left)
			{
				Object* object = new Object(BoxCollider(Vector2f(50, 50)));
				object->SetPosition(Vector2f(MousePos.x, MousePos.y));
				physicWorld.AddObject(object);
			}

			if (m_Window.GetEvent().mouseButton.button == sf::Mouse::Right)
			{
				if(objToMove == nullptr)
				{
					for (auto* obj : physicWorld.GetObjectList())
					{
						
						if (obj->Collider.Contains(PhysicEngine::Vector2f(MousePos.x, MousePos.y)))
						{
							objToMove = obj;			
						}
							
					}
				}
			}
		}

		if (m_Window.GetEvent().type == sf::Event::MouseButtonReleased)
		{
			if (m_Window.GetEvent().mouseButton.button == sf::Mouse::Right)
			{
				objToMove = nullptr;
			}
		}
	}
}
void Application::Update()
{
	m_Window.Update();
	UpdateView();

	if (objToMove != nullptr)
	{
		objToMove->Body.ApplyForce((objToMove->Body.Position - PhysicEngine::Vector2f(MousePos.x, MousePos.y)) * -50.f);
	}

	physicWorld.OnUpdate(m_Window.GetDeltaTime());

}
void Application::Render()
{
	m_Window.Clear();

	physicWorld.OnRender(m_Window.GetWindow());
	MousePos = m_Window.GetWindow().mapPixelToCoords(sf::Mouse::getPosition(m_Window.GetWindow()));

	m_Window.Display();
}

void Application::Run()
{
	while (m_Running)
	{
		this->Event();
		this->Update();
		this->Render();
	}
}
void Application::Close()
{
	m_Running = false;
}

void Application::UpdateView()
{
	float velocity = 400.f * this->m_Window.GetDeltaTime();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		view.move(sf::Vector2f(-1.f, 0.f) * velocity);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		view.move(sf::Vector2f(0.f, 1.f) * velocity);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		view.move(sf::Vector2f(1.f, 0.f) * velocity);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		view.move(sf::Vector2f(0.f, -1.f) * velocity);

	this->m_Window.SetView(view);
}


Application* CreateApplication()
{
	return new Application();;
}