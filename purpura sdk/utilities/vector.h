#pragma once

#include <sstream>

#ifdef NDEBUG
#define Assert( _exp ) ((void)0)
#else
#define Assert(x)
#endif

#define CHECK_VALID( _v ) 0

#define FastSqrt(x)	(sqrt)(x)

#define ALIGN16 __declspec(align(16))
#define VALVE_RAND_MAX 0x7fff
#define VectorExpand(v) (v).x, (v).y, (v).z

class vec2_t {
public:
	using vec_t = float;
	vec_t x, y;

	vec2_t(vec_t x = 0, vec_t y = 0) : x(x), y(y) {}
};

using vec2_t = vec2_t;

// pasted from valve l0l

class vec3_t
{
public:
	float x, y, z;
	vec3_t(void);
	vec3_t(float X, float Y, float Z);
	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	bool IsValid() const;
	float operator[](int i) const;
	float& operator[](int i);
	inline void Zero();
	bool operator==(const vec3_t& v) const;
	bool operator!=(const vec3_t& v) const;
	inline vec3_t&	operator+=(const vec3_t &v);
	inline vec3_t&	operator-=(const vec3_t &v);
	inline vec3_t&	operator*=(const vec3_t &v);
	inline vec3_t&	operator*=(float s);
	inline vec3_t&	operator/=(const vec3_t &v);
	inline vec3_t&	operator/=(float s);
	inline vec3_t&	operator+=(float fl);
	inline vec3_t&	operator-=(float fl);
	void crossproduct(vec3_t v1, vec3_t v2, vec3_t cross_p) const //ijk = xyz
	{
		cross_p.x = (v1.y * v2.z) - (v1.z * v2.y); //i
		cross_p.y = -((v1.x * v2.z) - (v1.z * v2.x)); //j
		cross_p.z = (v1.x * v2.y) - (v1.y * v2.x); //k
	}
	float Area()
	{
		return x * x + y * y + z * z;
	}
	float Magnitude()
	{
		return sqrt(Area());
	}
	float AngleTo(vec3_t& vOther)
	{
		return this->Dot(vOther) / (Magnitude() * vOther.Magnitude());
	}
	vec3_t Cross(const vec3_t & vOther) const
	{
		vec3_t res;
		crossproduct(*this, vOther, res);
		return res;
	}
	inline float	Length() const;
	inline float LengthSqr(void) const
	{
		CHECK_VALID(*this);
		return (x*x + y * y + z * z);
	}
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}
	vec3_t	Normalize();
	float	NormalizeInPlace();
	inline float	DistTo(const vec3_t &vOther) const;
	inline float	DistToSqr(const vec3_t &vOther) const;
	float	Dot(const vec3_t& vOther) const;
	float Dot2(const float * other) const;
	float	Length2D(void) const;
	float	Length2DSqr(void) const;
	void	MulAdd(const vec3_t& a, const vec3_t& b, float scalar);
	vec3_t& operator=(const vec3_t &vOther);
	vec3_t	operator-(void) const;
	vec3_t	operator+(const vec3_t& v) const;
	vec3_t	operator-(const vec3_t& v) const;
	vec3_t	operator*(const vec3_t& v) const;
	vec3_t	operator/(const vec3_t& v) const;
	vec3_t	operator*(float fl) const;
	vec3_t	operator/(float fl) const;
	// Base address...
	float* Base();
	float const* Base() const;

	float Size()
	{
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	auto dot2(float* other) const -> float
	{
		return x * other[0] + y * other[1] + z * other[2];
	}
};

//===============================================
inline void vec3_t::Init(float ix, float iy, float iz)
{
	x = ix; y = iy; z = iz;
	CHECK_VALID(*this);
}
//===============================================
inline vec3_t::vec3_t(float X, float Y, float Z)
{
	x = X; y = Y; z = Z;
	CHECK_VALID(*this);
}
//===============================================
inline vec3_t::vec3_t(void) { }
//===============================================
inline void vec3_t::Zero()
{
	x = y = z = 0.0f;
}
//===============================================
inline void VectorClear(vec3_t& a)
{
	a.x = a.y = a.z = 0.0f;
}
//===============================================
inline vec3_t& vec3_t::operator=(const vec3_t &vOther)
{
	CHECK_VALID(vOther);
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}
//===============================================
inline float& vec3_t::operator[](int i)
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}
//===============================================
inline float vec3_t::operator[](int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}
//===============================================
inline bool vec3_t::operator==(const vec3_t& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x == x) && (src.y == y) && (src.z == z);
}
//===============================================
inline bool vec3_t::operator!=(const vec3_t& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x != x) || (src.y != y) || (src.z != z);
}
//===============================================
inline void VectorCopy(const vec3_t& src, vec3_t& dst)
{
	CHECK_VALID(src);
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}
//===============================================
inline  vec3_t& vec3_t::operator+=(const vec3_t& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x += v.x; y += v.y; z += v.z;
	return *this;
}
//===============================================
inline  vec3_t& vec3_t::operator-=(const vec3_t& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}
//===============================================
inline  vec3_t& vec3_t::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline  vec3_t& vec3_t::operator*=(const vec3_t& v)
{
	CHECK_VALID(v);
	x *= v.x;
	y *= v.y;
	z *= v.z;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline vec3_t&	vec3_t::operator+=(float fl)
{
	x += fl;
	y += fl;
	z += fl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline vec3_t&	vec3_t::operator-=(float fl)
{
	x -= fl;
	y -= fl;
	z -= fl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline  vec3_t& vec3_t::operator/=(float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline  vec3_t& vec3_t::operator/=(const vec3_t& v)
{
	CHECK_VALID(v);
	Assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);
	x /= v.x;
	y /= v.y;
	z /= v.z;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline float vec3_t::Length(void) const
{
	CHECK_VALID(*this);

	float root = 0.0f;

	float sqsr = x * x + y * y + z * z;

	root = sqrt(sqsr);

	return root;
}
//===============================================
inline float vec3_t::Length2D(void) const
{
	CHECK_VALID(*this);

	float root = 0.0f;

	float sqst = x * x + y * y;

	root = sqrt(sqst);

	return root;
}
//===============================================
inline float vec3_t::Length2DSqr(void) const
{
	return (x*x + y * y);
}
//===============================================
inline vec3_t CrossProduct(const vec3_t& a, const vec3_t& b)
{
	return vec3_t(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}
//===============================================
float vec3_t::DistTo(const vec3_t &vOther) const
{
	vec3_t delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.Length();
}
float vec3_t::DistToSqr(const vec3_t &vOther) const
{
	vec3_t delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.LengthSqr();
}
//===============================================
inline vec3_t vec3_t::Normalize()
{
	vec3_t vector;
	float length = this->Length();

	if (length != 0)
	{
		vector.x = x / length;
		vector.y = y / length;
		vector.z = z / length;
	}
	else
	{
		vector.x = vector.y = 0.0f; vector.z = 1.0f;
	}

	return vector;
}
//===============================================
// changed that to fit awall, paste from xaE
inline float vec3_t::NormalizeInPlace()
{
	float radius = FastSqrt(x * x + y * y + z * z);

	// FLT_EPSILON is added to the radius to eliminate the possibility of divide by zero.
	float iradius = 1.f / (radius + FLT_EPSILON);

	x *= iradius;
	y *= iradius;
	z *= iradius;

	return radius;
}
//===============================================
inline void vec3_t::MulAdd(const vec3_t& a, const vec3_t& b, float scalar)
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
	z = a.z + b.z * scalar;
}
//===============================================
inline float VectorNormalize(vec3_t& v)
{
	Assert(v.IsValid());
	float l = v.Length();
	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		// FIXME:
		// Just copying the existing implemenation; shouldn't res.z == 0?
		v.x = v.y = 0.0f; v.z = 1.0f;
	}
	return l;
}
//===============================================
inline float VectorNormalize(float * v)
{
	return VectorNormalize(*(reinterpret_cast<vec3_t *>(v)));
}
//===============================================
inline vec3_t vec3_t::operator+(const vec3_t& v) const
{
	vec3_t res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

//===============================================
inline vec3_t vec3_t::operator-(const vec3_t& v) const
{
	vec3_t res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}
//===============================================
inline vec3_t vec3_t::operator*(float fl) const
{
	vec3_t res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}
//===============================================
inline vec3_t vec3_t::operator*(const vec3_t& v) const
{
	vec3_t res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}
//===============================================
inline vec3_t vec3_t::operator/(float fl) const
{
	vec3_t res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}
//===============================================
inline vec3_t vec3_t::operator/(const vec3_t& v) const
{
	vec3_t res;
	res.x = x / v.x;
	res.y = y / v.y;
	res.z = z / v.z;
	return res;
}
inline float vec3_t::Dot(const vec3_t& vOther) const
{
	const vec3_t& a = *this;

	return(a.x*vOther.x + a.y*vOther.y + a.z*vOther.z);
}
inline float vec3_t::Dot2(const float * other) const
{
	const vec3_t& a = *this;

	return a.x * other[0] + a.y * other[1] + a.z * other[2];
}

/*
	auto dot2(float* other) const -> float
	{
		return x * other[0] + y * other[1] + z * other[2];
	}
*/

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------

inline float VectorLength(const vec3_t& v)
{
	CHECK_VALID(v);
	return (float)FastSqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

//VECTOR SUBTRAC
inline void VectorSubtract(const vec3_t& a, const vec3_t& b, vec3_t& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

//VECTORADD
inline void VectorAdd(const vec3_t& a, const vec3_t& b, vec3_t& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------

inline float* vec3_t::Base()
{
	return (float*)this;
}

inline float const* vec3_t::Base() const
{
	return (float const*)this;
}

inline void VectorMAInline(const float* start, float scale, const float* direction, float* dest)
{
	dest[0] = start[0] + direction[0] * scale;
	dest[1] = start[1] + direction[1] * scale;
	dest[2] = start[2] + direction[2] * scale;
}

inline void VectorMAInline(const vec3_t& start, float scale, const vec3_t& direction, vec3_t& dest)
{
	dest.x = start.x + direction.x*scale;
	dest.y = start.y + direction.y*scale;
	dest.z = start.z + direction.z*scale;
}

inline void VectorMA(const vec3_t& start, float scale, const vec3_t& direction, vec3_t& dest)
{
	VectorMAInline(start, scale, direction, dest);
}

inline void VectorMA(const float * start, float scale, const float *direction, float *dest)
{
	VectorMAInline(start, scale, direction, dest);
}

inline unsigned long& FloatBits(float& f)
{
	return *reinterpret_cast<unsigned long*>(&f);
}

inline bool IsFinite(float f)
{
	return ((FloatBits(f) & 0x7F800000) != 0x7F800000);
}
