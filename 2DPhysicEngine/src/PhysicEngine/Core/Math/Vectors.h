#pragma once

#include "PhysicEngine/Core/Core.h"

namespace PhysicEngine {

	struct PHYSIC_ENGINE_API Vector2f
	{
	public:
		float X;
		float Y;

	public:
		Vector2f(const float& X = 0, const float& Y = 0) : X(X), Y(Y) {}

	public: // Operators

		Vector2f operator+(const Vector2f& other) const
		{
			return Vector2f(X + other.X, Y + other.Y);
		}
		Vector2f& operator+=(const Vector2f& other)
		{
			X += other.X;
			Y += other.Y;
			return *this;
		}

		Vector2f operator-(const Vector2f& other) const
		{
			return Vector2f(X - other.X, Y - other.Y);
		}
		Vector2f& operator-=(const Vector2f& other)
		{
			X -= other.X;
			Y -= other.Y;
			return *this;
		}

		Vector2f operator*(const Vector2f& other) const
		{
			return Vector2f(X * other.X, Y * other.Y);
		}

		Vector2f operator*(const float& scalar) const
		{
			return Vector2f(X * scalar, Y * scalar);
		}
		Vector2f& operator*=(const float& scalar)
		{
			X *= scalar;
			Y *= scalar;
			return *this;
		}

		Vector2f operator/(const float& scalar) const
		{
			return Vector2f(X / scalar, Y / scalar);
		}
		Vector2f& operator/=(const float& scalar)
		{
			X /= scalar;
			Y /= scalar;
			return *this;
		}

		Vector2f operator-() const {
			return Vector2f(-X, -Y);
		}
		Vector2f operator = (const Vector2f& other) {
			X = other.X;
			Y = other.Y;
			return *this;
		}

	public: // Logic operator
		bool operator==(const Vector2f& other) const
		{
			return X == other.X && Y == other.Y;
		}
	};

}