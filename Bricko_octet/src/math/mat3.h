#ifndef MAT3_INCLUDED
#define MAT3_INCLUDED

///This matrix will hold rotation for the transform
///Each vector is row vector of the matrix

// a b c
// d e f
// g h i

namespace octet { namespace math {

	class mat3{
	private:

	protected:		
		
	public:

		vec3 x;
		vec3 y;
		vec3 z;

		//constructors
		mat3(){}

		mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
			: x(a, b, c), y(d, e, f), z(g,h,i)
		{
			
		}

		mat3(const vec3& _x, const vec3& _y, const vec3& _z)
			: x(_x) , y(_y), z(_z)
		{

		}

		~mat3()
		{
		}

		//functions
		void Set(float a, float b, float c, float d, float e, float f, float g, float h, float i)
		{
			x[0] = a;
			x[1] = b;
			x[2] = c;
			y[0] = d;
			y[1] = e;
			y[2] = f;
			z[0] = g;
			z[1] = h;
			z[2] = i;
		}

		mat3 transpose() const
		{
			return  mat3();
		}

		mat3& loadIdentity()
		{
			x = vec3(1.0f, 0.0f, 0.0f);
			y = vec3(0.0f, 1.0f, 0.0f);
			z = vec3(0.0f, 0.0f, 1.0f);
			return *this;
		}

		const mat3 operator-(const mat3& rhs) const
		{
			return mat3(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		///Operator functions: right vector multiplication (N x N) * (N x 1)
		const vec3 operator*(const vec3& lhs) const
		{
			return vec3(
				x.x() *	lhs.x() + y.x() * lhs.y() + z.x() * lhs.z(),
				x.y() * lhs.x() + y.y() * lhs.y() + z.y() * lhs.z(),
				x.z() * lhs.x() + y.z() * lhs.y() + z.z() * lhs.z()
			);
		}

		const mat3 operator* (const mat3& rhs) const
		{
			return mat3(
				(*this * rhs.x),
				(*this * rhs.y),
				(*this * rhs.z)
			);
		}

		const mat3 operator* (float a) const
		{
			return mat3( x * a, y * a, z * a );
		}

		mat3& operator+=(const mat3& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		mat3& operator-=(const mat3& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		// access X row
		vec3& getX() { return x; }

		// access Y row
		vec3& getY() { return y; }

		// access Z row
		vec3& getZ() { return z; }

		//get column x
		vec3 colx() { return vec3(x[0], y[0], z[0]); };

		//get column y
		vec3 coly() { return vec3(x[1], y[1], z[1]); };
		
		//get column z
		vec3 colz() { return vec3(x[2], y[2], z[2]); };
	};

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

		det = 1.0 / m.z.dot(c);

		return mat3(
			a.x() * det, b.x() * det, c.x() * det,
			a.y() * det, b.y() * det, c.y() * det,
			a.z() * det, b.z() * det, c.z() * det
			);
	}
} }
#endif