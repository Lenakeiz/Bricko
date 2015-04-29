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
	};

} }