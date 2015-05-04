namespace octet {
	namespace brickophysics {
	
	struct brMassData{
		mat3 inertia;
		vec3 center;
		float mass
	};

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

		mat4t localtransform_mat4t;
		brTransform localtransform;

		vec3 halfextent;

		//Holding reference to its body
		brBody* body;

		float friction;
		float restitution;
		float density;

		void ComputeMass(brMassData& md) const
		{
			//Constructing inertia sensor
			float x2 = halfextent.x() * halfextent.x() * 4.0f;
			float y2 = halfextent.y() * halfextent.y() * 4.0f;
			float z2 = halfextent.z() * halfextent.z() * 4.0f;

			//calculating mass from density
			float m = 8.0f * halfextent.x() * halfextent.y() * halfextent.z() * density;

			float diagx = (1.0f / 12.0f) * m * (y2 + z2);
			float diagy = (1.0f / 12.0f) * m * (x2 + z2);
			float diagz = (1.0f / 12.0f) * m * (x2 + y2);
			
			mat3 inertia = diagonal(diagx, diagy, diagz);

			//Converting to local space
			//TODO
			//inertia = localtransform.rotation * inertia;
			//Setting mass data as a return
			//TODO
		}

		brBox()
		{
		}

		~brBox()
		{
		}
	};
} }


