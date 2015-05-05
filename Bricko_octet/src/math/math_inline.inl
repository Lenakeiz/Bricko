
namespace octet {
	namespace math{
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
	}
}
