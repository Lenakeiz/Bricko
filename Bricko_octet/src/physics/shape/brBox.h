namespace octet {
	namespace brickophysics {
	
	struct brBoxDef{

		float friction;
		float restitution;
		float density;
		
		mat4t transform;
		vec3 halfextent;

		brBoxDef()
		{
			friction = 0.4f;
			restitution = 0.2f;
			density = 1.0f;
			transform.loadIdentity();
			halfextent = vec3(1.0, 1.0f, 1.0f);
		}

		void Set(const mat4t& t, const vec3& he)
		{
			transform = t;
			halfextent = he * 0.5f;
		}

	};

	class brBox
	{
	public:

		brBox()
		{
		}

		~brBox()
		{
		}
	};
} }


