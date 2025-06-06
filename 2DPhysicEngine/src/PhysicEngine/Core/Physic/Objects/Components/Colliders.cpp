#include "Colliders.h"

namespace PhysicEngine {

	/*
		COLLIDER
	*/
	void Collider::ApplyRotation(std::vector<Vector2f>& vertices)
	{
		float cosAngle = Cos(Rotation);
		float sinAngle = Sin(Rotation);

		for (auto& vertex : vertices)
		{
			Vector2f relativeVertex = vertex - Position;

			vertex = Position + Vector2f(
				relativeVertex.X * cosAngle - relativeVertex.Y * sinAngle,
				relativeVertex.X * sinAngle + relativeVertex.Y * cosAngle
			);
		}
	}

	/*
		BOXCOLLIDER
	*/
	const bool& BoxCollider::Contains(const Vector2f& point) const
	{
		float halfX = Size.X / 2.f;
		float halfY = Size.Y / 2.f;

		return point.X > Position.X - halfX && point.X < (Position.X + halfX)
			&&
			point.Y > Position.Y - halfY && point.Y < (Position.Y + halfY);
	}
	std::vector<Vector2f> BoxCollider::GetVertices()
	{
		std::vector<Vector2f> vertices;

		vertices.push_back(Position + Vector2f(-Size.X / 2.f, -Size.Y / 2.f));
		vertices.push_back(Position + Vector2f(Size.X / 2.f, -Size.Y / 2.f));
		vertices.push_back(Position + Vector2f(Size.X / 2.f, Size.Y / 2.f));
		vertices.push_back(Position + Vector2f(-Size.X / 2.f, +Size.Y / 2.f));

		ApplyRotation(vertices);

		return vertices;
	}

	void BoxCollider::RenderDebug(sf::RenderWindow& renderWindow, const sf::Color& color)
	{
		sf::VertexArray debug(sf::LinesStrip, 5);

		for (std::size_t i = 0; i < 5; i++)
			debug[i].color = color;

		std::vector<Vector2f> vertices = GetVertices();

		debug[0].position = sf::Vector2f(vertices[0].X, vertices[0].Y);
		debug[1].position = sf::Vector2f(vertices[1].X, vertices[1].Y);
		debug[2].position = sf::Vector2f(vertices[2].X, vertices[2].Y);
		debug[3].position = sf::Vector2f(vertices[3].X, vertices[3].Y);
		debug[4].position = sf::Vector2f(vertices[0].X, vertices[0].Y);

		renderWindow.draw(debug);
	}

	/*
		CIRCLECOLLIDER
	*/
	const bool& CircleCollider::Contains(const Vector2f& point) const
	{
		return (PointsDistance(Position, point) <= Radius);
	}
	std::vector<Vector2f> CircleCollider::GetVertices()
	{
		std::vector<Vector2f> vertices;

		vertices.push_back(Position);

		return vertices;
	}

	void CircleCollider::RenderDebug(sf::RenderWindow& renderWindow, const sf::Color& color)
	{
		sf::CircleShape debug;
		debug.setRadius(Radius);
		debug.setPosition(sf::Vector2f(Position.X - Radius, Position.Y - Radius));
		debug.setFillColor(sf::Color::Transparent);
		debug.setOutlineThickness(1.f);
		debug.setOutlineColor(color);
		renderWindow.draw(debug);
	}

}