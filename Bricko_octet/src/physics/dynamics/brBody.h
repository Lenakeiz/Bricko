//#ifndef BRBODY_INCLUDED
//#define BRBODY_INCLUDED

namespace octet {
	namespace brickophysics {

		//class brBox;
		//class brBoxDef;
		//struct brMassData;

		enum BodyType{
			Static,
			Dynamic
		};

		//
		// This struct will hold the definition of the single body (took inspiration from Randy Gaul approach)
		//
		//
		struct brBodyDef
		{
			vec3 initialAxis;
			float initialAngle;
			vec3 initialPosition;
			vec3 intialLinearVelocity;
			vec3 intialAngularVelocity;

			BodyType bodyType;

			bool canSleep;
			bool isAwake;

			brBodyDef()
			{
				identity(initialAxis);
				identity(initialPosition);
				identity(intialLinearVelocity);
				identity(intialAngularVelocity);
				initialAngle = 0.0f;

				// Common default values
				bodyType = BodyType::Static;
				canSleep = true;
				isAwake = true;
			}
		};

		//
		// This class represent the physics body and will contain its properties such as 
		//
		// Bricko world body
		// a body has an orientation, with first derivatives. Subject to forces, torques and impulses.
		//
		class brBody
		{
		private:

			friend class brWorld;

			enum
			{
				bDynamic = 0x001,
				bStatic = 0x002,
				bCanSleep = 0x004,
				bIsAwake = 0x010,
			};
		
			void ClearAccumulators()
			{
				identity(force);
				identity(torque);
			}

			void CalcultateDerivedProperties()
			{
				mat3 inertia = diagonal(0.0f);
				vec3 lc;
				float finalmass = 0.0f;

				inverseInertiaBodyTensor = diagonal(0.0f);
				inverseInertiaWorldTensor = diagonal(0.0f);
				inverseMass = 0.0f;
				mass = 0.0f;

				if (type_flags & bStatic)
				{
					identity(localpos);
					//worldpos = transformMatrix.get_translation();
					worldpos = transform.position;
					return;
				}
			
				identity(lc);
				
				if (boxref != nullptr)
				{
					if (boxref->density != 0.0f)
					{
						brMassData data;
						boxref->ComputeMass(&data);
						finalmass = data.mass;
						inertia = data.inertia;
						lc = data.center * data.mass;
					}						
				}

				if (finalmass > 0.0f)
				{
					mass = finalmass;
					inverseMass = 1.0f / mass;
					lc *= inverseMass;

					mat3 id;
					id.loadIdentity();

					inertia -= (id * lc.dot(lc) - outer_product(lc, lc)) * finalmass;

					inverseInertiaBodyTensor = inverse(inertia);

				}
				else
				{
					inverseMass = 1.0f;
					inverseInertiaBodyTensor = diagonal(0.0f);
					inverseInertiaWorldTensor = diagonal(0.0f);
				}

				localpos = lc;
				worldpos = multiply(transform, lc);

			}

		public:
			///members
			//Properties of a rigid body can be divided in two:
			//Immutable such mass, inertia, damping
			//Mutable which depends on kinematics coming from the integrating of the simulation
			//Finally there are some properties that can be derived from others such as inverse of tensor in world coordinate

			///Holding inverse cause it s easy to handle static objects(Millington)
			float inverseMass;
			float mass;
			///Holding inverse of the body tensor given in body coordinate
			mat3 inverseInertiaBodyTensor;

			///Holding inverse of the body tensor in world space
			mat3 inverseInertiaWorldTensor;

			///Holding center position in world space
			vec3 worldpos;

			///Holding center position in local space
			vec3 localpos;

			///Holding orientation in world space
			quat orientation;

			///Holding linear velocity in world space
			vec3 linearVelocity;

			///Holding angular velocity in world space
			vec3 angularVelocity;

			///Holding transform matrix
			//mat4t transformMatrix;
			brTransform transform;

			///Holding accumulated force applied to the body to be applied next integration
			vec3 force;

			///Holding accumulated torque to be applied next integration
			vec3 torque;

			///Holding reference to the box
			brBox* boxref;

			///Holding a reference to the world, each type we create a body it will automatically add it to the world by using it as a friend class
			brWorld* world;

			///Holding reference to user data (can be useful in any application, taking inspiration from Bullet Physics
			void* user_data;

			///Holding type of body by setting flags to a signed int
			signed int type_flags;

		public:

			//public contructors
			brBody(const brBodyDef& def, brWorld* world)
			{
				linearVelocity = def.intialLinearVelocity;
				angularVelocity = def.intialAngularVelocity;
				orientation.set(def.initialAxis.normalize(), def.initialAngle);

				//TODO set the transform matrix
				//OLD VERSION
				//transformMatrix.loadIdentity();
				//transformMatrix.set_rotation(orientation.ToMat3());
				//transformMatrix.set_translation(def.initialPosition);

				//NEW VERSION
				transform.rotation = orientation.ToMat3();
				transform.position = def.initialPosition;

				identity(force);
				identity(torque);

				this->world = world;

				if (def.bodyType == Dynamic)
				{
					type_flags |= brBody::bDynamic;
				}
				else
				{
					type_flags |= brBody::bStatic;
					identity(linearVelocity);
					identity(angularVelocity);
				}

				if (def.canSleep)
				{
					type_flags |= brBody::bCanSleep;
				}

				if (def.isAwake)
				{
					type_flags |= brBody::bIsAwake;
				}
			}

			void ConnectBox(const brBoxDef& boxdef)
			{
				brBox* box = new brBox();
				box->localtransform = boxdef.transform;
				box->halfextent = boxdef.halfextent;

				box->collisionVolume = new brCollisionBox(aabb(vec3(0, 0, 0), boxdef.halfextent));
				box->collisionVolume->body = this;
				//TODO check if this can be removed
				box->body = this;

				box->friction = boxdef.friction;
				box->restitution = boxdef.restitution;
				box->density = boxdef.density;

				boxref = box;

				CalcultateDerivedProperties();

			}

			void ApplyLinearForce(const vec3& force)
			{
				this->force += mass * force;
			}

			void ApplyTorque(const vec3& torque)
			{
				this->torque += torque;
			}

			const vec3 GetLinearVelocity() const
			{
				return linearVelocity;
			}

			const vec3 GetAngularVelocity() const
			{
				return angularVelocity;
			}

			const mat4t GetTransformMat4t() const
			{
				return generate_mat4t(transform.rotation, transform.position);
			}

			const brTransform GetTransform()
			{
				return transform;
			}

			const vec3 GetPosition() const
			{
				return worldpos;
			}
			
			const quat GetOrientation() const
			{
				return orientation;
			}

			const float GetMass() const
			{
				return mass;
			}

			void SetUserData(void* pointer)
			{
				user_data = pointer;
			}

			void* GetUserData()
			{
				return user_data;
			}

			bool HasFiniteMass() const
			{
				return inverseMass > 0.0f;
			}

			void Integrate(float dt)
			{
				if (HasFiniteMass())
				{
					//Calculate inverse of inertia tensor in world coordinate
					mat3 rot = transform.rotation;
					inverseInertiaWorldTensor = rot * inverseInertiaBodyTensor * transpose(rot);

					linearVelocity  += (force * inverseMass) * dt;
					angularVelocity += (inverseInertiaWorldTensor * torque) * dt;
					
					//damping the force instead the velocity

					// Imposing drag for energy balance
					linearVelocity *= 1.0f / (1.0f + dt * 0.1f);
					angularVelocity *= 1.0f / (1.0f + dt * 0.1f);

					//Update positions and rotations
					worldpos += linearVelocity * dt;
					orientation.update(angularVelocity, dt);
					normalize(orientation);

					//finally update transform matrix
					transform.rotation = orientation.ToMat3();
					transform.position = worldpos - multiply(transform.rotation, localpos);
					
				}				
			}

			~brBody()
			{
			}

		};

} }
//#endif