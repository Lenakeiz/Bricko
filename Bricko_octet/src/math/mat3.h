#ifndef MAT3_INCLUDED
#define MAT3_INCLUDED

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

		///Operator functions
		const vec3 operator*(const vec3& rhs) const
		{
			return vec3(
				x.x() *	rhs.x() + y.x() * rhs.y() + z.x() * rhs.z(),
				x.y() * rhs.x() + y.y() * rhs.y() + z.y() * rhs.z(),
				x.z() * rhs.x() + y.z() * rhs.y() + z.z() * rhs.z()
			);
		}

		///This is used when setting a rotational matrix


	};

} }
#endif