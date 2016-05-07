#pragma once

#include <cmath>
#include <string>

static float Random(float min, float max)
{
	return min + static_cast<float>(rand()) * (max - min) / static_cast<float>(RAND_MAX);
}

template<class T, size_t D>
class vec;

template<class T, size_t D>
static float Dot(const vec<T, D>& a, const vec<T, D>& b)
{
	float res = 0;
	for (size_t i = 0; i < D; ++i)
	{
		res += a[i] * b[i];
	}

	return res;
}

template<class T>
class _vec4;

template<class T, size_t D>
class vec
{
public:
	vec()
	{
		for (size_t i = 0; i < D; ++i)
		{
			values[i] = 0;
		}
	}

	inline std::string ToString()
	{
		std::string res = "[ ";
		for (size_t i = 0; i < D; ++i)
		{
			if (i != 0)
				res += ", ";

			res += std::to_string(values[i]);
		}
		return res + " ]";
	}

	inline float Length()
	{
		return sqrtf(Dot(*this, *this));
	}

	inline float Normalize()
	{
		return (*this) / Length();
	}

	inline T Max()
	{
		T max = values[0];
		for (size_t i = 1; i < D; ++i)
		{
			if (values[i] > max) max = values[i];
		}
	}

	inline T Min()
	{
		T min = values[0];
		for (size_t i = 1; i < D; ++i)
		{
			if (values[i] < min) min = values[i];
		}
	}

	T& operator [] (size_t i) { return values[i]; }
	T operator [] (size_t i) const { return values[i]; }

	// +
	inline vec<T, D> operator+(const T& r) const
	{
		vec<T, D> res;
		for (size_t i = 0; i < D; ++i) {
			res[i] = values[i] + r;
		}
		return res;
	}

	inline friend vec<T, D> operator+(const T& r, const vec<T, D>& v)
	{
		vec<T, D> res;
		for (size_t i = 0; i < D; ++i) {
			res[i] = v[i] + r;
		}
		return res;
	}

	inline vec<T, D>& operator+=(const T& r)
	{
		for (size_t i = 0; i < D; ++i) {
			(*this)[i] = values[i] + r;
		}
		return *this;
	}

	inline vec<T, D> operator+(const vec<T, D>& v) const
	{
		vec<T, D> res;
		for (size_t i = 0; i < D; ++i) {
			res[i] = values[i] + v[i];
		}
		return res;
	}

	inline vec<T, D>& operator+=(const vec<T, D>& v)
	{
		for (size_t i = 0; i < D; ++i) {
			(*this)[i] = values[i] + v[i];
		}
		return *this;
	}

	// -

	inline vec<T, D> operator-(const T& r) const
	{
		vec<T, D> res;
		for (size_t i = 0; i < D; ++i) {
			res[i] = values[i] - r;
		}
		return res;
	}

	inline vec<T, D> operator-() const
	{
		vec<T, D> res;
		for (size_t i = 0; i < D; ++i) {
			res[i] = -values[i];
		}
		return res;
	}

	inline friend vec<T, D> operator-(const T& r, const vec<T, D>& v)
	{
		vec<T, D> res;
		for (size_t i = 0; i < D; ++i) {
			res[i] = v[i] - r;
		}
		return res;
	}

	inline vec<T, D>& operator-=(const T& r)
	{
		for (size_t i = 0; i < D; ++i) {
			(*this)[i] = values[i] - r;
		}
		return *this;
	}

	inline vec<T, D> operator-(const vec<T, D>& v) const
	{
		vec<T, D> res;
		for (size_t i = 0; i < D; ++i) {
			res[i] = values[i] - v[i];
		}
		return res;
	}

	inline vec<T, D>& operator-=(const vec<T, D>& v)
	{
		for (size_t i = 0; i < D; ++i) {
			(*this)[i] = values[i] - v[i];
		}
		return *this;
	}

	// *

	inline vec<T, D> operator*(const T& r) const
	{
		vec<T, D> res;
		for (size_t i = 0; i < D; ++i) {
			res[i] = values[i] * r;
		}
		return res;
	}

	inline friend vec<T, D> operator*(const T& r, const vec<T, D>& v)
	{
		vec<T, D> res;
		for (size_t i = 0; i < D; ++i) {
			res[i] = v[i] * r;
		}
		return res;
	}

	inline vec<T, D>& operator*=(const T& r)
	{
		for (size_t i = 0; i < D; ++i) {
			(*this)[i] = values[i] * r;
		}
		return *this;
	}

	// /

	inline vec<T, D> operator/(const T& r) const
	{
		vec<T, D> res;
		for (size_t i = 0; i < D; ++i) {
			res[i] = values[i] / r;
		}
		return res;
	}

	inline friend vec<T, D> operator/(const T& r, const vec<T, D>& v)
	{
		vec<T, D> res;
		for (size_t i = 0; i < D; ++i) {
			res[i] = v[i] / r;
		}
		return res;
	}

	inline vec<T, D>& operator/=(const T& r)
	{
		for (size_t i = 0; i < D; ++i) {
			(*this)[i] = values[i] / r;
		}
		return *this;
	}

	// == and !=

	inline bool operator==(const vec<T, D>& v) const
	{
		for (size_t i = 0; i < D; ++i) {
			if ((*this)[i] != v[i]) return false;
		}
		return true;
	}

	inline bool operator!=(const vec<T, D>& v) const
	{
		return !operator==(v);
	}

	operator _vec4<T>()
	{
		return _vec4<T>(values[0], values[1], values[2], values[3]);
	}
private:
	T values[D];
};

template<class T, size_t D>
vec<T, D> Lerp(const vec<T, D>& a, const vec<T, D>& b, T lerpFactor)
{ 
	return (b - a) * lerpFactor + a; 
}

template<class T>
class _vec2 : public vec<T, 2>
{
public:
	_vec2() : x((*this)[0]), y((*this)[1]) {}

	_vec2(const _vec2<T>& v) : x((*this)[0]), y((*this)[1])
	{
		(*this)[0] = v[0];
		(*this)[1] = v[1];
	}

	_vec2(T x, T y) : x((*this)[0]), y((*this)[1])
	{
		(*this)[0] = x;
		(*this)[1] = y;
	}

	T& x;
	T& y;

	_vec2<T>& operator=(const _vec2<T>& v)
	{
		(*this).x = v.x;
		(*this).y = v.y;
		return *this;
	}
};

template<class T>
class _vec3 : public vec<T, 3>
{
public:
	_vec3() : x((*this)[0]), y((*this)[1]), z((*this)[2]) {}

	_vec3(const _vec3<T>& v) : x((*this)[0]), y((*this)[1]), z((*this)[2])
	{
		(*this)[0] = v[0];
		(*this)[1] = v[1];
		(*this)[2] = v[2];
	}

	_vec3(T x, T y, T z) : x((*this)[0]), y((*this)[1]), z((*this)[2])
	{
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
	}

	T& x;
	T& y;
	T& z;

	_vec3<T>& operator=(const _vec3<T>& v)
	{
		(*this).x = v.x;
		(*this).y = v.y;
		(*this).z = v.z;
		return *this;
	}
};

template<class T>
class _vec4 : public vec<T, 4>
{
public:
	_vec4() : x((*this)[0]), y((*this)[1]), z((*this)[2]), w((*this)[3]) {}

	_vec4(const _vec4<T>& v) : x((*this)[0]), y((*this)[1]), z((*this)[2]), w((*this)[3])
	{
		(*this)[0] = v[0];
		(*this)[1] = v[1];
		(*this)[2] = v[2];
		(*this)[3] = v[3];
	}

	_vec4(T x, T y, T z, T w) : x((*this)[0]), y((*this)[1]), z((*this)[2]), w((*this)[3])
	{
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
		(*this)[3] = w;
	}

	T& x;
	T& y;
	T& z;
	T& w;

	_vec4<T>& operator=(const _vec4<T>& v)
	{
		(*this).x = v.x;
		(*this).y = v.y;
		(*this).z = v.z;
		(*this).w = v.w;
		return *this;
	}
};

template<class T>
static _vec3<T> Cross(const _vec3<T>& a, const _vec3<T>& b)
{
	return _vec3<T>(a[1] * b[2] - a[2] * b[1],
					a[2] * b[0] - a[0] * b[2],
					a[0] * b[1] - a[1] * b[0]);
}

typedef _vec2<size_t> uvec2;
typedef _vec2<int> ivec2;
typedef _vec2<float> vec2;
typedef _vec2<double> dvec2;

typedef _vec3<size_t> uvec3;
typedef _vec3<int> ivec3;
typedef _vec3<float> vec3;
typedef _vec3<double> dvec3;

typedef _vec4<size_t> uvec4;
typedef _vec4<int> ivec4;
typedef _vec4<float> vec4;
typedef _vec4<double> dvec4;

template<class T, size_t D>
class mat
{
public:
	mat<T, D>& InitIdentity()					// i->   0 1 2 3
	{											// j   0
		for (size_t i = 0; i < D; ++i)			// |   1
		{										// V   2
			for (size_t j = 0; j < D; ++j)		//     3
			{									//
				if (i == j)						//
					m[i][j] = T(1);
				else
					m[i][j] = T(0);
			}
		}

		return *this;
	}

	mat<T, D>& InitScale(const vec<T, D - 1>& v)
	{
		for (size_t i = 0; i < D; ++i)
		{
			for (size_t j = 0; j < D; ++j)
			{
				if ((i == j) && (i != D - 1))
					m[i][j] = v[i];
				else
					m[i][j] = T(0);
			}
		}

		m[D - 1][D - 1] = T(1);

		return *this;
	}

	mat<T, D>& InitTranslation(const vec<T, D - 1>& v)
	{
		for (size_t i = 0; i < D; ++i)
		{
			for (size_t j = 0; j < D; ++j)
			{
				if ((i == D - 1) && (j != D - 1))
					m[i][j] = v[j];
				else if (i == j)
					m[i][j] = T(1);
				else
					m[i][j] = T(0);
			}
		}

		m[D - 1][D - 1] = T(1);

		return *this;
	}

	mat<T, D> Transpose() const
	{
		mat<T, D> t;
		for (size_t j = 0; j < D; ++j) 
		{
			for (size_t i = 0; i < D; ++i) 
			{
				t[i][j] = m[j][i];
			}
		}
		return t;
	}

	mat<T, D> Inverse() const
	{
		int i, j, k;
		mat<T, D> s;
		mat<T, D> t(*this);

		for (i = 0; i < D - 1; ++i) 
		{
			int pivot = i;

			T pivotsize = t[i][i];

			if (pivotsize < 0)
				pivotsize = -pivotsize;

			for (j = i + 1; j < D; j++) 
			{
				T tmp = t[j][i];

				if (tmp < 0)
					tmp = -tmp;

				if (tmp > pivotsize) 
				{
					pivot = j;
					pivotsize = tmp;
				}
			}

			if (!pivotsize) return mat<T, D>();

			if (pivot != i) 
			{
				for (j = 0; j < D; j++) 
				{
					T tmp;

					tmp = t[i][j];
					t[i][j] = t[pivot][j];
					t[pivot][j] = tmp;

					tmp = s[i][j];
					s[i][j] = s[pivot][j];
					s[pivot][j] = tmp;
				}
			}

			for (j = i + 1; j < D; j++) 
			{
				T f = t[j][i] / t[i][i];

				for (k = 0; k < D; k++) {
					t[j][k] -= f * t[i][k];
					s[j][k] -= f * s[i][k];
				}
			}
		}

		for (i = D - 1; i >= 0; --i) 
		{
			T f;

			if (!(f = t[i][i])) return mat<T, D>();

			for (j = 0; j < D; j++) 
			{
				t[i][j] /= f;
				s[i][j] /= f;
			}

			for (j = 0; j < i; j++) 
			{
				f = t[j][i];

				for (k = 0; k < D; k++) 
				{
					t[j][k] -= f * t[i][k];
					s[j][k] -= f * s[i][k];
				}
			}
		}

		return s;
	}

	mat<T, D> operator*(const mat<T, D>& v) const
	{
		mat<T, D> ret;
		for (size_t i = 0; i < D; ++i)
		{
			for (size_t j = 0; j < D; ++j)
			{
				ret.m[i][j] = T(0);
				for (size_t k = 0; k < D; ++k)
					ret.m[i][j] += m[k][j] * v.m[i][k];
			}
		}
		return ret;
	}

	vec<T, D> Transform(const vec<T, D>& v) const
	{
		vec<T, D> ret;

		for (size_t i = 0; i < D; ++i)
		{
			ret[i] = 0;
			for (size_t j = 0; j < D; ++j)
				ret[i] += m[j][i] * v[j];
		}

		return ret;
	}

	vec<T, D - 1> Transform(const vec<T, D - 1>& v) const
	{
		vec<T, D> u;

		for (size_t i = 0; i < D - 1; ++i)
			u[i] = v[i];

		u[D - 1] = T(1);

		vec<T, D> t = Transform(u);
		vec<T, D - 1> ret;

		for (size_t i = 0; i < D - 1; ++i)
			ret[i] = t[i];

		return ret;
	}

	void Set(size_t x, size_t y, T val) { m[x][y] = val; }

	const T* operator[](int index) const { return m[index]; }
	T* operator[](int index) { return m[index]; }

	inline std::string ToString() const
	{
		std::string res = "[";

		for (size_t i = 0; i < D; ++i)
		{
			if (!i)
				res += "[";
			else
				res += " [";

			for (size_t j = 0; j < D; ++j)
			{
				if (j)
					res += ", ";
				res += std::to_string(m[j][i]);
			}

			if (i != D - 1)
				res += " ],\n";
		}

		return res + " ]]";
	}
private:
	T m[D][D];
};

template<typename T>
class _mat4 : public mat<T, 4>
{
public:
	_mat4() { }

	template<size_t D>
	_mat4(const mat<T, D>& v)
	{
		if (D < 4)
		{
			this->InitIdentity();

			for (size_t i = 0; i < D; ++i)
			{
				for (size_t j = 0; j < D; ++j)
				{
					(*this)[i][j] = v[i][j];
				}
			}
		}
		else
		{
			for (size_t i = 0; i < 4; ++i)
			{
				for (size_t j = 0; j < 4; ++j)
				{
					(*this)[i][j] = v[i][j];
				}
			}
		}
	}

	_mat4(T n)
	{
		for (size_t i = 0; i < 4; ++i)
		{
			for (size_t j = 0; j < 4; ++j)
			{
				(*this)[i][j] = n;
			}
		}
	}

	_mat4(T xx, T xy, T xz, T xw,
		  T yx, T yy, T yz, T yw,
		  T zx, T zy, T zz, T zw,
		  T wx, T wy, T wz, T ww)
	{
		(*this)[0][0] = xx; (*this)[1][0] = xy; (*this)[2][0] = xz; (*this)[3][0] = xw;
		(*this)[0][1] = yx; (*this)[1][1] = yy; (*this)[2][1] = yz; (*this)[3][1] = yw;
		(*this)[0][2] = zx; (*this)[1][2] = zy; (*this)[2][2] = zz; (*this)[3][2] = zw;
		(*this)[0][3] = wx; (*this)[1][3] = wy; (*this)[2][3] = wz; (*this)[3][3] = ww;
	}

	_mat4<T> InitRotationEuler(T rotateX, T rotateY, T rotateZ)
	{
		_mat4<T> rx, ry, rz;

		T sinx = static_cast<T>(sin(rotateX));
		T siny = static_cast<T>(sin(rotateY));
		T sinz = static_cast<T>(sin(rotateZ));

		T cosx = static_cast<T>(cos(rotateX));
		T cosy = static_cast<T>(cos(rotateY));
		T cosz = static_cast<T>(cos(rotateZ));


		rx[0][0] = T(1);  rx[1][0] = T(0);  rx[2][0] = T(0);  rx[3][0] = T(0);
		rx[0][1] = T(0);  rx[1][1] = cosx;  rx[2][1] =-sinx;  rx[3][1] = T(0);
		rx[0][2] = T(0);  rx[1][2] = sinx;  rx[2][2] = cosx;  rx[3][2] = T(0);
		rx[0][3] = T(0);  rx[1][3] = T(0);  rx[2][3] = T(0);  rx[3][3] = T(1);

		ry[0][0] = cosy;  ry[1][0] = T(0);  ry[2][0] =-siny;  ry[3][0] = T(0);
		ry[0][1] = T(0);  ry[1][1] = T(1);  ry[2][1] = T(0);  ry[3][1] = T(0);
		ry[0][2] = siny;  ry[1][2] = T(0);  ry[2][2] = cosy;  ry[3][2] = T(0);
		ry[0][3] = T(0);  ry[1][3] = T(0);  ry[2][3] = T(0);  ry[3][3] = T(1);

		rz[0][0] = cosz;  rz[1][0] =-sinz;  rz[2][0] = T(0);  rz[3][0] = T(0);
		rz[0][1] = sinz;  rz[1][1] = cosz;  rz[2][1] = T(0);  rz[3][1] = T(0);
		rz[0][2] = T(0);  rz[1][2] = T(0);  rz[2][2] = T(1);  rz[3][2] = T(0);
		rz[0][3] = T(0);  rz[1][3] = T(0);  rz[2][3] = T(0);  rz[3][3] = T(1);

		*this = rz * ry * rx;

		return *this;
	}

	_mat4<T> InitRotationFromVectors(const _vec3<T>& a, const _vec3<T>& b, const _vec3<T>& c)
	{
		(*this)[0][0] = c.x;   (*this)[1][0] = c.y;   (*this)[2][0] = c.z;   (*this)[3][0] = T(0);
		(*this)[0][1] = b.x;   (*this)[1][1] = b.y;   (*this)[2][1] = b.z;   (*this)[3][1] = T(0);
		(*this)[0][2] = a.x;   (*this)[1][2] = a.y;   (*this)[2][2] = a.z;   (*this)[3][2] = T(0);
		(*this)[0][3] = T(0);  (*this)[1][3] = T(0);  (*this)[2][3] = T(0);  (*this)[3][3] = T(1);

		return *this;
	}

	_mat4<T> InitRotationFromDirection(const _vec3<T>& forward, const _vec3<T>& up)
	{
		_vec3<T> a = Normalize(forward);
		_vec3<T> c = Cross(Normalize(up), a);
		_vec3<T> b = Cross(a, c);

		return InitRotationFromVectors(a, b, c);
	}

	_mat4<T> InitPerspective(T fov, T aspectRatio, T zNear, T zFar)
	{
		const T zRange = zNear - zFar;
		const T tanHalfFOV = tanf(fov / T(2));

		(*this)[0][0] = T(1) / (tanHalfFOV * aspectRatio); (*this)[1][0] = T(0);   (*this)[2][0] = T(0);            (*this)[3][0] = T(0);
		(*this)[0][1] = T(0);                   (*this)[1][1] = T(1) / tanHalfFOV; (*this)[2][1] = T(0);            (*this)[3][1] = T(0);
		(*this)[0][2] = T(0);                   (*this)[1][2] = T(0);            (*this)[2][2] = (-zNear - zFar) / zRange; (*this)[3][2] = T(2)*zFar*zNear / zRange;
		(*this)[0][3] = T(0);                   (*this)[1][3] = T(0);            (*this)[2][3] = T(1);            (*this)[3][3] = T(0);

		return *this;
	}

	_mat4<T> InitOrthographic(T left, T right, T bottom, T top, T near, T far)
	{
		(*this)[0][0] = 2.0f / (right - left);
		(*this)[0][1] = 0.0f;
		(*this)[0][2] = 0.0f;
		(*this)[0][3] = 0.0f;

		(*this)[1][0] = 0.0f;
		(*this)[1][1] = 2.0f / (top - bottom);
		(*this)[1][2] = 0.0f;
		(*this)[1][3] = 0.0f;

		(*this)[2][0] = 0.0f;
		(*this)[2][1] = 0.0f;
		(*this)[2][2] = -2.0f / (far - near);
		(*this)[2][3] = 0.0f;

		(*this)[3][0] = (right + left) / (left - right);
		(*this)[3][1] = (top + bottom) / (bottom - top);
		(*this)[3][2] = near / (near - far);
		(*this)[3][3] = 1.0f;

		return *this;
	}

	_mat4<T> LookAt(const _vec3<T>& eye, const _vec3<T>& center, const _vec3<T>& up)
	{
		_vec3<T> f = Normalize(center - eye);
		_vec3<T> s = Normalize(Cross(f, up));
		_vec3<T> u = Normalize(Cross(s, f));

		(*this)[0][0] = s.x;
		(*this)[1][0] = s.y;
		(*this)[2][0] = s.z;
		(*this)[0][1] = u.x;
		(*this)[1][1] = u.y;
		(*this)[2][1] = u.z;
		(*this)[0][2] =-f.x;
		(*this)[1][2] =-f.y;
		(*this)[2][2] =-f.z;
		(*this)[3][0] =-Dot(s, eye);
		(*this)[3][1] =-Dot(u, eye);
		(*this)[3][2] = Dot(f, eye);
		return (*this);
	}
};

template<typename T>
class _mat3 : public mat<T, 3>
{
public:
	_mat3() { }

	template<size_t D>
	_mat3(const mat<T, D>& r)
	{
		if (D < 3)
		{
			this->InitIdentity();

			for (unsigned int i = 0; i < D; i++)
			for (unsigned int j = 0; j < D; j++)
				(*this)[i][j] = r[i][j];
		}
		else
		{
			for (unsigned int i = 0; i < 3; i++)
			for (unsigned int j = 0; j < 3; j++)
				(*this)[i][j] = r[i][j];
		}
	}
};

typedef mat<float, 2> mat2;
typedef mat<double, 2> dmat2;

typedef _mat3<float> mat3;
typedef _mat3<double> dmat3;

typedef _mat4<float> mat4;
typedef _mat4<double> dmat4;

class quat : public _vec4<float>
{
public:
	quat(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f)
	{
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
		(*this)[3] = w;
	}

	quat(const vec4& r)
	{
		(*this)[0] = r[0];
		(*this)[1] = r[1];
		(*this)[2] = r[2];
		(*this)[3] = r[3];
	}

	quat(const vec3& axis, float angle)
	{
		float sinHalfAngle = sinf(angle / 2);
		float cosHalfAngle = cosf(angle / 2);

		(*this)[0] = axis.x * sinHalfAngle;
		(*this)[1] = axis.y * sinHalfAngle;
		(*this)[2] = axis.z * sinHalfAngle;
		(*this)[3] = cosHalfAngle;
	}

	quat(const mat4& m)
	{
		float trace = m[0][0] + m[1][1] + m[2][2];

		if (trace > 0)
		{
			float s = 0.5f / sqrtf(trace + 1.0f);
			(*this)[3] = 0.25f / s;
			(*this)[0] = (m[1][2] - m[2][1]) * s;
			(*this)[1] = (m[2][0] - m[0][2]) * s;
			(*this)[2] = (m[0][1] - m[1][0]) * s;
		}
		else if (m[0][0] > m[1][1] && m[0][0] > m[2][2])
		{
			float s = 2.0f * sqrtf(1.0f + m[0][0] - m[1][1] - m[2][2]);
			(*this)[3] = (m[1][2] - m[2][1]) / s;
			(*this)[0] = 0.25f * s;
			(*this)[1] = (m[1][0] + m[0][1]) / s;
			(*this)[2] = (m[2][0] + m[0][2]) / s;
		}
		else if (m[1][1] > m[2][2])
		{
			float s = 2.0f * sqrtf(1.0f + m[1][1] - m[0][0] - m[2][2]);
			(*this)[3] = (m[2][0] - m[0][2]) / s;
			(*this)[0] = (m[1][0] + m[0][1]) / s;
			(*this)[1] = 0.25f * s;
			(*this)[2] = (m[2][1] + m[1][2]) / s;
		}
		else
		{
			float s = 2.0f * sqrtf(1.0f + m[2][2] - m[1][1] - m[0][0]);
			(*this)[3] = (m[0][1] - m[1][0]) / s;
			(*this)[0] = (m[2][0] + m[0][2]) / s;
			(*this)[1] = (m[1][2] + m[2][1]) / s;
			(*this)[2] = 0.25f * s;
		}

		float length = Length();
		(*this)[3] = (*this)[3] / length;
		(*this)[0] = (*this)[0] / length;
		(*this)[1] = (*this)[1] / length;
		(*this)[2] = (*this)[2] / length;
	}

	inline mat4 ToRotationMatrix() const
	{
		vec3 forward = vec3(2.0f * (x * z - w * y), 2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y));
		vec3 up = vec3(2.0f * (x*y + w*z), 1.0f - 2.0f * (x*x + z*z), 2.0f * (y*z - w*x));
		vec3 right = vec3(1.0f - 2.0f * (y*y + z*z), 2.0f * (x*y -w*z), 2.0f * (x*z + w*y));

		return mat4().InitRotationFromVectors(forward, up, right);
	}

	inline quat operator=(const vec<float, 4U>& r)
	{
		(*this)[0] = r[0];
		(*this)[1] = r[1];
		(*this)[2] = r[2];
		(*this)[3] = r[3];
	}

	inline quat operator=(const quat& r)
	{
		(*this)[0] = r[0];
		(*this)[1] = r[1];
		(*this)[2] = r[2];
		(*this)[3] = r[3];
	}
private:

};

static quat NLerp(const quat& a, const quat& b, float lerpFactor, bool shortestPath)
{
	quat correctedDest;

	if (shortestPath && Dot(a, b) < 0)
		correctedDest = -b;
	else
		correctedDest = b;

	return quat((Lerp(a, correctedDest, lerpFactor)).Length());
}

static quat SLerp(const quat& a, const quat& b, float lerpFactor, bool shortestPath)
{
	static const float EPSILON = 1e3;

	float cos = Dot(a, b);
	quat correctedDest;

	if (shortestPath && cos < 0)
	{
		cos *= -1;
		correctedDest = b * -1;
	}
	else
		correctedDest = b;

	if (fabs(cos) >(1 - EPSILON))
		return NLerp(a, correctedDest, lerpFactor, false);

	float sin = (float)sqrtf(1.0f - cos * cos);
	float angle = atan2(sin, cos);
	float invSin = 1.0f / sin;

	float srcFactor = sinf((1.0f - lerpFactor) * angle) * invSin;
	float destFactor = sinf((lerpFactor)* angle) * invSin;

	return quat(a * srcFactor + correctedDest * destFactor);
}