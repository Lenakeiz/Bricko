////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012-2014
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.
//
// Vector class
//

namespace octet { namespace math {
  class quat : public vec4
  {
  public:
	//Chuck
	//Added default constructor for quaternion
	quat() : vec4(0, 0, 0, 0) {}
    quat(float x, float y, float z, float w) : vec4(x, y, z, w) {}
    quat(const vec4 &r) { *(vec4*)this = r; }
	void set(const vec3& axis, float angle)
	{
		float halfangle = 0.5f * angle;
		float s = sinf(halfangle);
		x() = axis[0] * s;
		y() = axis[1] * s;
		z() = axis[2] * s;
		w() = cos(halfangle);		
	}

	quat operator*(const quat &r) const { return quat(qmul(r)); }
    quat operator*(float r) const { return quat((vec4&)*this * r); }
    quat &operator*=(const quat &r) { *(vec4*)this = qmul(r); return *this; }
    quat conjugate() const { return qconj(); }
    vec4 rotate(const vec4 &r) const { return (*this * r) * conjugate(); }

  };

} }

