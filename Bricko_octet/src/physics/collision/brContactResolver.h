namespace octet {
	namespace brickophysics {

		class brContactResolver
		{
			

		public:
			
			///I will avoid considering static and dynamic friction, I will use just a friction set to the world and passed to all contacts
			static void ResolveVelocities(brContact& contact)
			{

				brBody* a = contact.bodies[0];
				brBody* b = contact.bodies[1];

				if (!a->HasFiniteMass() && !b->HasFiniteMass())
					return;

				const float epsilon = 0.00000001f;

				vec3 relativeContactPosition[2]       = { vec3(0.0f), vec3(0.0f) };
				vec3 velocityAtContactPosition[2]     = { vec3(0.0f), vec3(0.0f) }; 
				vec3 velocityPerUnitImpulse[2]        = { vec3(0.0f), vec3(0.0f) };
				vec3 tangentVelocityPerUnitImpulse[2] = { vec3(0.0f), vec3(0.0f) };

				float finalModuleVelocity = 0.0f;
				float finalTangentVelocity = 0.0f;

				relativeContactPosition[0] = contact.contactPoint - a->transform.position;
				relativeContactPosition[1] = contact.contactPoint - b->transform.position;

				velocityAtContactPosition[0] = a->HasFiniteMass() ? a->linearVelocity + a->angularVelocity.cross(relativeContactPosition[0]) : vec3(0.0f);
				velocityAtContactPosition[1] = b->HasFiniteMass() ? b->linearVelocity + b->angularVelocity.cross(relativeContactPosition[1]) : vec3(0.0f);
				vec3 velocityDifference = velocityAtContactPosition[0] - velocityAtContactPosition[1];
				
				//projecting the velocity along contact normal
				float seperatingComponent = velocityDifference.dot(contact.contactNormal);

				//there is already a component for which they are separating
				if (seperatingComponent > 0.0f)
					return;

				float linearComp = contact.contactNormal.squared() * (a->inverseMass + b->inverseMass);

				//Evaluating normal components
				{
					//restitution coefficient (c)
					float c = contact.restitution;
					//Calculating the linear component of the velocity change
										
					if (a->HasFiniteMass())
					{
						//torque per unit impulse
						vec3 tPerUnitImpulse = relativeContactPosition[0].cross(contact.contactNormal);
						//rotation per unit impulse
						tPerUnitImpulse = a->inverseInertiaWorldTensor * tPerUnitImpulse;
						velocityPerUnitImpulse[0] = tPerUnitImpulse.cross(relativeContactPosition[0]);
					}

					if (b->HasFiniteMass())
					{
						//torque per unit impulse
						vec3 tPerUnitImpulse = relativeContactPosition[1].cross(contact.contactNormal);
						//rotation per unit impulse
						tPerUnitImpulse = b->inverseInertiaWorldTensor * tPerUnitImpulse;
						velocityPerUnitImpulse[1] = tPerUnitImpulse.cross(relativeContactPosition[1]);
					}

					float norm_angular = (velocityPerUnitImpulse[0] + velocityPerUnitImpulse[1]).dot(contact.contactNormal);

					float totat_normal = linearComp + norm_angular + 0.000001f;

					finalModuleVelocity = -1.0f * (1.0f + c) * velocityDifference.dot(contact.contactNormal) / totat_normal;
				
					//Applying changes to bodies
					if (a->HasFiniteMass())
					{
						a->linearVelocity += (-1.0f * contact.contactNormal) * (totat_normal * a->inverseMass);

						vec3 angular_change = a->inverseInertiaWorldTensor * (relativeContactPosition[0] * finalModuleVelocity);
						//a->angularVelocity += angular_change;
					}

					if (b->HasFiniteMass())
					{
						b->linearVelocity += (-1.0f * contact.contactNormal) * (totat_normal * b->inverseMass);

						vec3 angular_change = b->inverseInertiaWorldTensor * (relativeContactPosition[1] * finalModuleVelocity);
						//b->angularVelocity += angular_change;
					}
				}
				
				//Evaluating tangent component for friction
				/*{
					vec3 tan = velocityDifference - contact.contactNormal * velocityDifference.dot(contact.contactNormal);
					tan.normalize();

					if (a->HasFiniteMass())
					{
						vec3 tPerUnitImpulse = relativeContactPosition[0].cross(tan);
						tPerUnitImpulse = a->inverseInertiaWorldTensor * (tPerUnitImpulse);
						tangentVelocityPerUnitImpulse[0] = tPerUnitImpulse.cross(relativeContactPosition[0]);
					}

					if (b->HasFiniteMass())
					{
						vec3 tPerUnitImpulse = relativeContactPosition[1].cross(tan);
						tPerUnitImpulse = b->inverseInertiaWorldTensor * (tPerUnitImpulse);
						tangentVelocityPerUnitImpulse[1] = tPerUnitImpulse.cross(relativeContactPosition[1]);
					}

					float tan_angular = (tangentVelocityPerUnitImpulse[0] + tangentVelocityPerUnitImpulse[1]).dot(tan);

					float tan_total = linear_comp + tan_angular;
					if (tan_total > 0.0f)
					{
						finalTangentVelocity = -1.0f * velocityDifference.dot(tan) / tan_total;
						float friction = contact.friction;
					}

				}*/

			}

			static void ResolvePositions(brContact& contact)
			{
				brBody* b[2];				
				const float threshold = 0.0004f;

				const float epsilon = 0.00000001f;

				float s[2] = { 1.0f, -1.0f };

				for (unsigned i = 0; i < 2; i++)
				{
					b[i] = contact.bodies[i];
					
					vec3 relativeContactPos = contact.contactPoint - b[i]->transform.position;
					
					if (b[i]->HasFiniteMass())
					{
						//Same as in Velocities, calculating angular component of the collision
						vec3 angularInertiaWorld = relativeContactPos.cross(contact.contactNormal);
						angularInertiaWorld = b[i]->inverseInertiaWorldTensor * angularInertiaWorld;
						angularInertiaWorld = angularInertiaWorld.cross(relativeContactPos);
						
						float angularInertia = angularInertiaWorld.dot(contact.contactNormal);
						
						float linearInertia = b[i]->inverseMass;
						float totalInertia = linearInertia + angularInertia;
						float inverseInertia = totalInertia < epsilon ? 0.0f : 1.0f / totalInertia;
						
						float linearMove = s[i] * contact.penetration * linearInertia * inverseInertia;
						float angularMove = s[i] * contact.penetration * angularInertia * inverseInertia;

						vec3 proj = relativeContactPos + (contact.contactNormal * ((-1.0f * relativeContactPos).dot(contact.contactNormal)));
						
						float maxMovement = proj.length() * threshold;
						float totalMove = angularMove + linearMove;

						if (angularMove < -maxMovement)
						{							
							angularMove = -maxMovement;
						}
						else if (angularMove > maxMovement)
						{
							angularMove = maxMovement;
						}

						linearMove = totalMove - angularMove;

						vec3 angularChange(0.0f);
						if (abs(angularMove) > epsilon)
						{
							vec3 impulseTorque = relativeContactPos.cross(contact.contactNormal);
							angularChange = angularInertia < epsilon ? vec3(0.0f) : (b[i]->inverseInertiaWorldTensor * impulseTorque) * (angularMove / angularInertia);
						}

						b[i]->transform.position += contact.contactNormal * linearMove;						
						
						quat q = b[i]->orientation;
						q.update(angularChange, 1.0f);
						q = normalize(q);
						//b[i]->orientation = q;
						//b[i]->transform.rotation = q.ToMat3();
						//b[i]->inverseInertiaWorldTensor = b[i]->transform.rotation *  b[i]->inverseInertiaBodyTensor * transpose(b[i]->transform.rotation);
						//b[i]->transform.position = b[i]->worldpos - multiply(b[i]->transform.rotation, b[i]->localpos);

					}
				}



			}

			static void ResolveContact(brContact& contact, int iterations)
			{
				//Need to add awake status check
				ResolvePositions(contact);
				ResolveVelocities(contact);				
			}

			brContactResolver()
			{
			}

			~brContactResolver()
			{
			}
		};
	}
}