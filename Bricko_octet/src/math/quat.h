////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012-2014
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.
//
// Quaternion class
//

#include "mat3.h"

namespace octet { namespace math {

  //The real part is the last element of the Vector	
  class quat : public vec4
  {
  public:
	//Chuck
	//Added default constructor for quaternion
	quat() : vec4(0, 0, 0, 0) {}
    quat(float x, float y, float z, float w) : vec4(x, y, z, w) {}
    quat(const vec4 &r) { *(vec4*)this = r; }
	//Using to set the quaternion (Jason Gregory - Game Engine Architecture)
	void set(const vec3& axis, float angle)
	{
		float halfangle = 0.5f * angle;
		float s = sinf(halfangle);
		x() = axis[0] * s;
		y() = axis[1] * s;
		z() = axis[2] * s;
		w() = cosf(halfangle);		
	}
	///Millington
	void update(const vec3& vt, double dt)
	{
		float dt_f = (float)dt;
		quat q(vt.x() * dt_f, vt.y() * dt_f, vt.z() * dt_f, 0.0f);

		q *= *this;

		x() = q.x() * 0.5f;
		y() = q.y() * 0.5f;
		z() = q.z() * 0.5f;
		w() = q.w() * 0.5f;

	}
	const mat3 ToMat3()
	{
		float xx = x() * x();
		float yy = y() * y();
		float zz = z() * z();

		float xy = x() * y();
		float xz = x() * z();
		float xw = x() * w();

		float zw = z() * w();
		
		float yw = y() * w();
		float yz = y() * z();

		return mat3(
			1 - 2 * yy - 2 * zz, 2 * xy + 2 * zw, 2 * xz - 2 * yw,
			2 * xy - 2 * zw, 1 - 2 * xx - 2 * zz, 2 * yz + 2 * xw,
			2 * xz + 2 * yw, 2 * yz - 2 * xw, 1 - 2 * xx - 2 * yy
			);
	}
	quat operator*(const quat &r) const { return quat(qmul(r)); }
    quat operator*(float r) const { return quat((vec4&)*this * r); }
    quat &operator*=(const quat &r) { *(vec4*)this = qmul(r); return *this; }
    quat conjugate() const { return qconj(); }
    vec4 rotate(const vec4 &r) const { return (*this * r) * conjugate(); }

  };

  inline const quat normalize(const quat& q)
  {	  
	  float d = q.x() * q.x() + q.y() * q.y() + q.z() * q.z() + q.w() * q.w();

	  //Check zero length quat
	  if (d == 0)
		  return quat();

	  d = (float)1.0 / sqrt(d);
	  float x = q.x() * d;
	  float y = q.y() * d;
	  float z = q.z() * d;
	  float w = q.w() * d;

	  return quat(x, y, z, w);
  }

} }

