//#ifndef BRBOX_INCLUDED
//#define BRBOX_INCLUDED

namespace octet {
	namespace brickophysics {
	
	struct brMassData{
		mat3 inertia;
		vec3 center;
		float mass;
	};

	struct brTransform
	{
		vec3 position;
		mat3 rotation;
	};

	struct brBoxDef{

		float friction;
		float restitution;
		float density;
		
		mat4t transform_mat4t;
		brTransform transform;

		vec3 halfextent;

		brBoxDef()
		{
			friction = 0.4f;
			restitution = 0.2f;
			density = 1.0f;
			identity(transform.position);
			transform.rotation.loadIdentity();
			halfextent = vec3(1.0, 1.0f, 1.0f);
		}

		void Set(const mat4t& t, const vec3& he)
		{
			transform_mat4t = t;
			halfextent = he * 0.5f;
		}

		void Set(const brTransform& t, const vec3& he)
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

		aabb collisionVolume;

		//Holding reference to its body
		brBody* body;

		float friction;
		float restitution;
		float density;

		void ComputeMass(brMassData* md) const
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
			inertia = localtransform.rotation * inertia * transpose(localtransform.rotation);
			mat3 id;
			id.loadIdentity();
			
			//Setting mass data as a return
			inertia += (id * localtransform.position.dot(localtransform.position) - outer_product(localtransform.position, localtransform.position))* m;
		
			md->center = localtransform.position;
			md->inertia = inertia;
			md->mass = m;
		}

		brBox()
		{
		}

		~brBox()
		{
		}
	};

	inline const vec3 multiply(const brTransform& t, const vec3& v)
	{
		return vec3(t.rotation * v + t.position);
	}

	inline void identity(brTransform& t)
	{
		identity(t.position);
		t.rotation.loadIdentity();
	}
} }
//#endif

