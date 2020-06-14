#pragma once


template<template<typename> class TT, typename T, int ... Indexes>
class swizzle
{
	T v[sizeof...(Indexes)];
public:
	TT<T>& operator=(const TT<T>& rhs)
	{
		int indexes[] = { Indexes... };
		for (int i = 0; i < sizeof...(Indexes); i++)
		{
			v[indexes[i]] = rhs[i];
		}
		return *(TT<T>*)this;
	}
	operator TT<T>() const
	{
		return TT<T>(v[Indexes]...);
	}
};

template <typename T>
struct Vec2
{
	Vec2(T x, T y) : x(x), y(y)
	{

	}

	template<typename TT>
	Vec2(const Vec2<TT>& a) : x((T)a.x), y((T)a.y)
	{

	}

	//Vec2(const Vec2& a) : x(a.x), y(a.y)
	//{

	//}

	explicit Vec2(T* arr) : x(arr[0]), y(arr[1])
	{

	}

	Vec2 operator-(const Vec2& b) const
	{
		return Vec2(x - b.x, y - b.y);
	}

	operator T* ()
	{
		return (T*)this;
	}

	T operator[](int index) const
	{
		return ((T*)(*this))[index];
	}


	union
	{
		struct { T x, y; };
		swizzle<Vec2, T, 0, 1> xy;
		swizzle<Vec2, T, 1, 0> yx;
	};



};


template <typename T>
struct Vec3
{
	Vec3(T x, T y, T z) : x(x), y(y), z(z)
	{

	}

	Vec3(const Vec3& a) : x(a.x), y(a.y), z(a.z)
	{

	}

	explicit Vec3(T* arr) : x(arr[0]), y(arr[1]), z(arr[2])
	{

	}

	operator T* ()
	{
		return (T*)this;
	}

	T operator[](int index) const
	{
		return ((T*)(*this))[index];
	}

	union
	{
		struct { T x, y, z; };
		struct { T r, g, b; };
		swizzle<Vec3, T, 0, 1> xy;
		swizzle<Vec3, T, 1, 0> yx;
		swizzle<Vec3, T, 0, 2> xz;
		swizzle<Vec3, T, 2, 0> zx;
		swizzle<Vec3, T, 1, 2> yz;
		swizzle<Vec3, T, 2, 1> zy;
		swizzle<Vec3, T, 0, 1, 2> xyz;
		swizzle<Vec3, T, 1, 0, 2> yxz;
		swizzle<Vec3, T, 0, 2, 1> xzy;
		swizzle<Vec3, T, 2, 0, 1> zxy;
		swizzle<Vec3, T, 1, 2, 0> yzx;
		swizzle<Vec3, T, 2, 1, 0> zyx;
	};
};

template<typename T>
Vec3<T> operator* (float value, const Vec3<T>& v)
{
	return Vec3<T>(value * v.x, value * v.y, value * v.z);
}

template<typename T>
Vec3<T> operator+ (const Vec3<T>& a, const Vec3<T>& b)
{
	return Vec3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
}

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;

typedef Vec3<float> Vec3f;
typedef Vec3<float> Vec3i;


