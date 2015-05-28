namespace octet {
	namespace brickophysics {

		class brCollisionBox
		{

		public:

			aabb shape;

			///Set a reference to its body, can be usefulfor calculation and to update the transform		
			brBody* body;
			
			/**
			*  This holds the world transform of the object:
			*  must be linked to the Rigid body transform
			*/

			//THIS IS DANGEROUS SINCE WE NEED ALWAYS TO SYNC THIS MATRIX WITH THE BODY
			// I WILL USE ALWAYS THE REFERENCE TO THE BODY AND GET THE TRANSFORM
			mat4t transform;

			vec3 get_axis(unsigned idx) const
			{
				//assert(body != nullptr);
				//return (body->transformMatrix)[idx].xyz();
				//mat4t transformy = body->GetTransformMat4t();
				//return transformy[idx].xyz();
				return transform[idx].xyz();
			}

			vec3 get_x_axis() const
			{
				return transform.x().xyz();
			}

			vec3 get_y_axis() const
			{
				return transform.y().xyz();
			}

			vec3 get_z_axis() const
			{
				return transform.z().xyz();
			}

			vec3 get_w_axis() const
			{
				return transform.w().xyz();
			}

			brCollisionBox()
			{
			}

			brCollisionBox(aabb_in s)
			{
				shape = s;
			}

			~brCollisionBox()
			{
			}
		};

		/**
		* Given the box transform we perform the calculation along the given axis   
		*/
		static inline float transformToAxis(const brCollisionBox &box, const vec3& axis)
		{
			return
				box.shape.get_half_extent().x() * fabs(axis.dot(box.get_axis(0))) +
				box.shape.get_half_extent().y() * fabs(axis.dot(box.get_axis(1))) +
				box.shape.get_half_extent().z() * fabs(axis.dot(box.get_axis(2)));
		}

		/**
		* This function checks if the two boxes overlap
		* along the given axis. The final parameter 
		* is used to detect if overlapping
		*/
		static inline bool overlapOnAxis(const brCollisionBox& a, const brCollisionBox& b, const vec3& axis, const vec3& centre)
		{
			float aProject = transformToAxis(a, axis);
			float bProject = transformToAxis(b, axis);

			float distance = fabs(centre.dot(axis));

			//checking the overlap
			return (distance < aProject + bProject);
		}

		static inline float penetrationOnAxis(const brCollisionBox &a, const brCollisionBox &b, const vec3 &axis, const vec3 &centre)
		{
			float aProject = transformToAxis(a, axis);
			float bProject = transformToAxis(b, axis);

			float distance = fabs(centre.dot(axis));

			//checking the overlap
			return aProject + bProject - distance;
		}

		static inline bool tryAxis(const brCollisionBox& a, const brCollisionBox& b, const vec3& axis, const vec3& centre, unsigned index, float& smallestPenetration, unsigned &smallestCase)
		{
			float penetration = penetrationOnAxis(a, b, axis, centre);
			if (penetration < 0) return false;
			if (penetration < smallestPenetration)
			{
				smallestPenetration = penetration;
				smallestCase = index;
			}
			return true;
		}
	}
}

