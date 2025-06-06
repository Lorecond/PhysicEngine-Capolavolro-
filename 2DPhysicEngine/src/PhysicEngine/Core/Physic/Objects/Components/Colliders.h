#pragma once

#include "Component.h"

#include <SFML/Graphics.hpp>

namespace PhysicEngine {

	/*
		COLLIDER
	*/
	struct PHYSIC_ENGINE_API Collider
		: public Component
	{
	public:
		float Rotation = 0.f;

	public: // Virtual
		virtual const bool& Contains(const Vector2f& point) const = 0;
		virtual std::vector<Vector2f> GetVertices() = 0;

		virtual void RenderDebug(sf::RenderWindow& renderWindow, const sf::Color& color = sf::Color::Red) = 0;

	protected:
		void ApplyRotation(std::vector<Vector2f>& vertices);
	};
	/*
		BOXCOLLIDER
	*/
	struct PHYSIC_ENGINE_API BoxCollider
		: public Collider
	{
	public:
		BoxCollider(const Vector2f& size = Vector2f(1.f, 1.f)) : Size(size) {}

	public:
		Vector2f Size;

	public:
		const bool& Contains(const Vector2f& point) const override;
		std::vector<Vector2f> GetVertices() override;

		void RenderDebug(sf::RenderWindow& renderWindow, const sf::Color& color = sf::Color::Red) override;
	};
	/*
		CIRCLECOLLIDER
	*/
	struct PHYSIC_ENGINE_API CircleCollider
		: public Collider
	{
	public:
		CircleCollider(const float& radius = 0.f) : Radius(radius) {}

	public:
		float Radius;

	public: 
		const bool& Contains(const Vector2f& point) const override;
		std::vector<Vector2f> GetVertices() override;

		void RenderDebug(sf::RenderWindow& renderWindow, const sf::Color& color = sf::Color::Red) override;
	};


	
}