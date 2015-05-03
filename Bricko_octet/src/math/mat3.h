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
		vec3 x;
		vec3 y;
		vec3 z;
		
	public:

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

		///Operator functions: left vector multiplication ( 1 x N ) * (N x N)
		const vec3 operator*(const vec3& lhs) const
		{
			return vec3(
				x.x() *	lhs.x() + y.x() * lhs.y() + z.x() * lhs.z(),
				x.y() * lhs.x() + y.y() * lhs.y() + z.y() * lhs.z(),
				x.z() * lhs.x() + y.z() * lhs.y() + z.z() * lhs.z()
			);
		}

		// access X row
		vec3& getX() { return x; }

		// access Y row
		vec3& getY() { return y; }

		// access Z row
		vec3& getZ() { return z; }


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

} }
#endif