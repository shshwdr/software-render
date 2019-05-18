#pragma once

#include <cmath>
using namespace std;
template <class t> struct Vec2
{
	union {
		struct {
			t x, y;
		};
		t raw[2];
	};
	Vec2() :x(0), y(0) {}
	Vec2(t _x, t _y) :x(_x), y(_y) {}
	inline Vec2<t> operator +(const Vec2<t> &val) const {
		return Vec2(x + val.x, y + val.y);
	}
	inline Vec2<t> operator -(const Vec2<t> &val) const {
		return Vec2(x - val.x, y - val.y);
	}
	inline Vec2<t> operator *(float f) const {
		return Vec2(x*f, y*f);
	}
	template <class t> friend ostream& operator<<(ostream& s, Vec2<t> &val) {
		s << "(" << val.x << "," << val.y << ")" << endl;
		return s;
	}
};
//template <class t> friend ostream& operator<<(ostream& s, Vec2<t> &val) 
typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;


template <class t> struct Vec3
{
	union {
		struct {
			t x, y, z;
		};
		t raw[3];
	};
	Vec3() :x(0), y(0), z(0) {}
	Vec3(t _x, t _y, t _z) :x(_x), y(_y), z(_z) {}
	inline Vec3<t> operator +(const Vec3<t> &val) const {
		return Vec3(x + val.x, y + val.y, z+val.z);
	}
	inline Vec3<t> operator -(const Vec3<t> &val) const {
		return Vec3(x - val.x, y - val.y, z - val.z);
	}
	friend ostream& operator<<(ostream& s, Vec3<t> &val) {
		s << "(" << val.x << "," << val.y << "," << val.z << ")" << endl;
		return s;
	}
};
//template <class t>
//friend ostream& operator<<(ostream& s, Vec3<t> &val) 
typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;
