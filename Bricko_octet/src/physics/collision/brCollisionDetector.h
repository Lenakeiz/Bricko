namespace octet {
	namespace brickophysics {


	///CHAPTER 13 MILLINGTON
	//#define CHECK_OVERLAP(axis, index) \
	//	if (!tryAxis(a, b, (axis), centre, (index), penetration, best)) return 0;

		class brCollisionDetector
		{
		public:

			/// Method called when vertex and face are interconnected
			static void generateContactPointFaceBoxBoxData(
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

				//TODO check consistency with this transformation into world coordinates
				contact->contactPoint = (b.transform * vec4(vertex, 0.0f)).xyz();
				contact->setData(a.body, b.body, data->friction, data->restitution);
			}
		
			///Calculating point of maximum close
			static vec3 contactPointOnEdges
				(
					const vec3& point_one,
					const vec3& axis_one,
					float one_size,
					const vec3& point_two,
					const vec3& axis_two,
					float two_size,
					bool useA
				)
			{
								
				float denominator = axis_one.squared() * axis_two.squared() - axis_one.dot(axis_two) * axis_one.dot(axis_two);

				//Check if parallel lines
				if (fabs(denominator) < 0.0001f)
				{
					return useA ? point_one : point_two;
				}

				float dot_one_dist = axis_one.dot(point_one - point_two);
				float dot_two_dist = axis_two.dot(point_one - point_two);

				float a = (axis_one.dot(axis_two) * dot_two_dist - axis_two.squared() * dot_one_dist) / denominator;
				float b = (axis_one.squared() * dot_two_dist - axis_one.dot(axis_two) * dot_one_dist) / denominator;

				if (a > one_size || a < -one_size || b > two_size || b < -two_size)
				{
					return useA ? point_one : point_two;
				}
				else
				{
					vec3 contact_one = point_one + axis_one * a;
					vec3 contact_two = point_two + axis_two * b;

					return contact_one * 0.5f + contact_two * 0.5;
				}

			}

			static void generateContactPointEdgeEdgeBoxData(
				const brCollisionBox &a,
				const brCollisionBox &b,
				const vec3 &centre,
				brCollisionData *data,
				unsigned best,
				float penetration
				)
			{
				//Getting the best axis (edge edge case is not with principal axis so we needd to reconstruct the correct cross product)
				unsigned aAxisIndex = best / 3;
				unsigned bAxisIndex = best % 3;

				vec3 aAxis = a.get_axis(aAxisIndex);
				vec3 bAxis = b.get_axis(bAxisIndex);
				vec3 axis = aAxis.cross(bAxis).normalize();

				//Detecting direction of the axis, make it point from a to b
				if (axis.dot(centre) > 0) axis = axis * (-1.0f);

				vec3 aPointOnAEdge = a.shape.get_half_extent();
				vec3 bPointOnBEdge = b.shape.get_half_extent();

				for (unsigned i = 0; i < 3; i++)
				{
					if (i == aAxisIndex) aPointOnAEdge[i] = 0;
					else if (a.get_axis(i).dot(axis) > 0) aPointOnAEdge[i] = -aPointOnAEdge[i];

					if (i == bAxisIndex) bPointOnBEdge[i] = 0;
					else if (b.get_axis(i).dot(axis) > 0) bPointOnBEdge[i] = -bPointOnBEdge[i];
				}

				//Transforming into world coordinates
				aPointOnAEdge = (a.transform * vec4(aPointOnAEdge, 0.0f)).xyz();
				bPointOnBEdge = (b.transform * vec4(bPointOnBEdge, 0.0f)).xyz();

				//Here there are two middle points and the direction for the edges.
				//Finding now the point of closest approach between this two lines
				vec3 vertex = contactPointOnEdges(
					aPointOnAEdge, aAxis, a.shape.get_half_extent()[aAxisIndex],
					bPointOnBEdge, bAxis, b.shape.get_half_extent()[bAxisIndex],
					best > 2
					);

				//Adding the contact to the list
				brContact* contact = data->contacts;
				
				contact->penetration = penetration;
				contact->contactNormal = axis;
				contact->contactPoint = vertex;
				contact->setData(a.body, b.body,
					data->friction, data->restitution);


				data->addContacts(1);


			}

			static unsigned generateBoxesData(const brCollisionBox& a, const brCollisionBox& b, brCollisionData* data)
			{
				vec3 centre = b.get_axis(3) - a.get_axis(3);

				float penetration = 150000;
				unsigned best = 0xffffff;

				// There are 6 axes (3 per boxes) 
				// Their cross product add nine more axis to try

				//First box
				if (!tryAxis(a, b, (a.get_axis(0)), centre, 0, penetration, best)) return 0;
				if (!tryAxis(a, b, (a.get_axis(1)), centre, 1, penetration, best)) return 0;
				if (!tryAxis(a, b, (a.get_axis(2)), centre, 2, penetration, best)) return 0;

				//Second box
				if (!tryAxis(a, b, (b.get_axis(0)), centre, 3, penetration, best)) return 0;
				if (!tryAxis(a, b, (b.get_axis(1)), centre, 4, penetration, best)) return 0;
				if (!tryAxis(a, b, (b.get_axis(2)), centre, 5, penetration, best)) return 0;

				//we store the best at this point because later we can encouter almost parallel edge collisions
				unsigned bestSingleAxis = best;

				if (!tryAxis(a, b, (a.get_axis(0).cross(b.get_axis(0))), centre, 6, penetration, best)) return 0;
				if (!tryAxis(a, b, (a.get_axis(0).cross(b.get_axis(1))), centre, 7, penetration, best)) return 0;
				if (!tryAxis(a, b, (a.get_axis(0).cross(b.get_axis(2))), centre, 8, penetration, best)) return 0;
				if (!tryAxis(a, b, (a.get_axis(1).cross(b.get_axis(0))), centre, 9, penetration, best)) return 0;
				if (!tryAxis(a, b, (a.get_axis(1).cross(b.get_axis(1))), centre, 10, penetration, best)) return 0;
				if (!tryAxis(a, b, (a.get_axis(1).cross(b.get_axis(2))), centre, 11, penetration, best)) return 0;
				if (!tryAxis(a, b, (a.get_axis(2).cross(b.get_axis(0))), centre, 12, penetration, best)) return 0;
				if (!tryAxis(a, b, (a.get_axis(2).cross(b.get_axis(1))), centre, 13, penetration, best)) return 0;
				if (!tryAxis(a, b, (a.get_axis(2).cross(b.get_axis(2))), centre, 14, penetration, best)) return 0;

				assert(best != 0xffffff);

				//smallest penetration along principal axis. This is considered as point face for collisions
				if (best < 3)
				{
					//Vertex of box two is inside face of box one
					generateContactPointFaceBoxBoxData(a, b, centre, data, best, penetration);
					return 1;
				}
				else if (best < 6)
				{
					//Millington using the same function from above but swapping the two boxes, need to change direction to the centre vector as well
					generateContactPointFaceBoxBoxData(b, a, centre *(-1.0f), data, best - 3, penetration);
					return 1;
				}
				else
				{
					//This is edge to edge collision
					generateContactPointEdgeEdgeBoxData(a, b, centre, data, best - 6, penetration);
					return 1;
				}

				return 0;

			};

		};
	}
}

