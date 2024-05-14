#pragma once

namespace Arkanoid
{
	template<typename T>
	class Vector2D
	{
	public:
		T GetX() const { return x; }
		void SetX(T newX) { x = newX; }

		T GetY() const { return y; }
		void SetY(T newY) { y = newY; }
	private:
		T x = (T)0;
		T y = (T)0;
	};

	using Vector2Df = Vector2D<float>;
	using Vector2Di = Vector2D<int>;
	using Position = Vector2Df;

	template<typename T>
	Vector2D<T> operator*(const Vector2D<T>& vector, const T& scalar)
	{
		return { vector.GetX() * scalar, vector.GetY() * scalar };
	}

	template<typename T>
	Vector2D<T> operator+(const Vector2D<T>& lhs, const Vector2D<T>& rhs)
	{
		return { lhs.GetX() + rhs.GetX(), lhs.GetY() + rhs.GetY() };
	}

	template<typename T>
	Vector2D<T> operator-(const Vector2D<T>& lhs, const Vector2D<T>& rhs)
	{
		return { lhs.GetX() - rhs.GetX(), lhs.GetY() - rhs.GetY() };
	}

	template<typename T>
	bool operator==(const Vector2D<T>& lhs, const Vector2D<T>& rhs)
	{
		return lhs.GetX() == rhs.GetX() && lhs.GetY() == rhs.GetY();
	}

	template<typename T>
	float GetVectorLength(const Vector2D<T>& vector)
	{
		return sqrtf(vector.GetX() * vector.GetX() + vector.GetY() * vector.GetY());
	}

	// This complex template allows us to convert any vector type to any other vector type (like our Vector2D to SFML's Vector and vice versa)
	template<typename U, typename V>
	U Convert(const V& v)
	{
		// decltype deduces type from expression
		return { static_cast<decltype(U::x)>(v.x), static_cast<decltype(U::y)>(v.y) };
	}
}
