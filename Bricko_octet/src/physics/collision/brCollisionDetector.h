namespace octet {
	namespace brickophysics {


	#define CHECK_OVERLAP(axis, index) \
		if (!tryAxis(a, b, (axis), centre, (index), penetration, best))

		class brCollisionDetector
		{
		public:

			/// Method called when vertex and face 
			void generateContactPointFaceBoxBoxData(
				const brCollisionBox &a,
				const brCollisionBox &b,
				const vec3 &centre,
				brCollisionData *data,
				unsigned best,
				float penetration
				)
			{
				brContact* contact = data->contacts;

				// Given the axis there are two faces that could result into the collision
				// This is the simplest case and the axis result into the normal of the two faces to be considered
				vec3 normal = a.get_axis(best);
				if (normal.dot(centre) > 0)
				{ 
					normal *= -1.0f;
				}

				// Finding the vertex that s colliding
				vec3 vertex = b.shape.get_half_extent();

				if (b.get_axis(0).dot(normal) < 0) vertex.x() = -vertex.x();
				if (b.get_axis(1).dot(normal) < 0) vertex.y() = -vertex.y();
				if (b.get_axis(2).dot(normal) < 0) vertex.z() = -vertex.z();

				contact->contactNormal = normal;
				contact->penetration = penetration;

				//TODO check consistency f this transformation
				contact->contactPoint = (b.transform * vec4(vertex, 0.0f)).xyz();
				//TODO set Data for this contact
				//contact->setData()
			}
				

			static unsigned generateBoxesData(const brCollisionBox& a, const brCollisionBox& b, brCollisionData* data)
			{
				vec3 centre = b.get_axis(3) - a.get_axis(3);

				float penetration = 150000;
				unsigned best = 0xffffff;

				// There are 6 axes (3 per boxes) 
				// Their cross product add nine more axis to try
				CHECK_OVERLAP(a.get_axis(0), 0);
				CHECK_OVERLAP(a.get_axis(1), 1);
				CHECK_OVERLAP(a.get_axis(2), 2);

				CHECK_OVERLAP(b.get_axis(0), 3);
				CHECK_OVERLAP(b.get_axis(1), 4);
				CHECK_OVERLAP(b.get_axis(2), 5);

				unsigned bestSingleAxis = best;

				CHECK_OVERLAP(a.get_axis(0).cross(b.get_axis(0)), 6);
				CHECK_OVERLAP(a.get_axis(0).cross(b.get_axis(1)), 7);
				CHECK_OVERLAP(a.get_axis(0).cross(b.get_axis(2)), 8);
				CHECK_OVERLAP(a.get_axis(1).cross(b.get_axis(0)), 9);
				CHECK_OVERLAP(a.get_axis(1).cross(b.get_axis(1)), 10);
				CHECK_OVERLAP(a.get_axis(1).cross(b.get_axis(2)), 11);
				CHECK_OVERLAP(a.get_axis(2).cross(b.get_axis(0)), 12);
				CHECK_OVERLAP(a.get_axis(2).cross(b.get_axis(1)), 13);
				CHECK_OVERLAP(a.get_axis(2).cross(b.get_axis(2)), 14);

				assert(best != 0xffffff);

				//smallest penetration along principal axis. This is considered as point face for collisions
				if (best < 3)
				{
					//Vertex of box two is inside face of box one
					generateContactPointFaceBoxBoxData(a, b, centre, data, best, penetration);
				}
			};

		};
	}
}

