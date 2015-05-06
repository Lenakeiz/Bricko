
namespace octet {
	namespace math{

		inline const mat4t generate_mat4t(const mat3& r, const vec3&v)
		{
			return mat4t(vec4(r.x,0.0f),vec4(r.y,0.0f),vec4(r.z,0.0f),vec4(v,1.0f));
		}

		inline const vec3 multiply(const mat3& r, const vec3& v)
		{
			return r * v;
		}

		inline const mat3 diagonal(float r)
		{
			return mat3(
				r, 0.0f, 0.0f,
				0.0f, r, 0.0f,
				0.0f, 0.0f, r
				);
		}

		inline const mat3 diagonal(float a, float b, float c)
		{
			return mat3(
				a, 0.0f, 0.0f,
				0.0f, b, 0.0f,
				0.0f, 0.0f, c
				);
		}

		inline const mat3 inverse(const mat3& m)
		{
			vec3 a, b, c;
			float det;

			a = cross(m.y, m.z);
			b = cross(m.z, m.x);
			c = cross(m.x, m.y);

			det = 1.0f / m.z.dot(c);

			return mat3(
				a.x() * det, b.x() * det, c.x() * det,
				a.y() * det, b.y() * det, c.y() * det,
				a.z() * det, b.z() * det, c.z() * det
				);
		}

		inline const mat3 outer_product(const vec3 &r, const vec3& l)
		{
			vec3 a = r * l.x();
			vec3 b = r * l.y();
			vec3 c = r * l.z();

			return mat3(
				a.x(), a.y(), a.z(),
				b.x(), b.y(), b.z(),
				c.x(), c.y(), c.z()
				);
		}

		inline const mat3 transpose(const mat3& m)
		{
			return mat3(
				m.x.x(), m.y.x(), m.z.x(),
				m.x.y(), m.y.y(), m.z.y(),
				m.x.z(), m.y.z(), m.z.z()
				);
		}
	}
}
