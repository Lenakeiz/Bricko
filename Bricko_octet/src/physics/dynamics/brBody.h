#ifndef BRBODY_INCLUDED
#define BRBODY_INCLUDED

namespace octet {
	namespace brickophysics {

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
				Dynamic = 0x001,
				Static = 0x002,
				CanSleep = 0x004,
				IsAwake = 0x010,
			};
		
		protected:
			///members
			//Properties of a rigid body can be divided in two:
			//Immutable such mass, inertia, damping
			//Mutable which depends on kinematics coming from the integrating of the simulation
			//Finally there are some properties that can be derived from others such as inverse of tensor in world coordinate

			///Holding inverse cause it s easy to handle static objects(Millington)
			double inverseMass;
			double mass;
			///Holding inverse of the body tensor given in body coordinate
			mat3 inverseInertiaBodyTensor;

			///Holding inverse of the body tensor in world space
			mat3 inverseInertiaWorldTensor;

			///Holding position in world space
			vec3 worldpos;

			///Holding orientation in world space
			quat orientation;

			///Holding linear velocity in world space
			vec3 linearVelocity;

			///Holding angular velocity in world space
			vec3 angularVelocity;

			///Holding transform matrix
			mat4t transformMatrix;

			///Holding accumulated force applied to the body to be applied next integration
			vec3 force;

			///Holding accumulated torque to be applied next integration
			vec3 torque;

			///Holding a reference to the world, each type we create a body it will automatically add it to the world by using it as a friend class
			brWorld* world;

			///Holding type of body by setting flags to a signed int
			signed int type_flags;

		public:

			//public contructors
			brBody(const brBodyDef& def, brWorld* world)
			{
				this->linearVelocity = def.intialLinearVelocity;
				this->angularVelocity = def.intialAngularVelocity;
				this->orientation.set(def.initialAxis.normalize(), def.initialAngle);
				identity(force);
				identity(torque);
				this->world = world;

				if (def.bodyType == Dynamic)
				{
					type_flags |= brBody::Dynamic;
				}
				else
				{
					type_flags |= brBody::Static;
					identity(linearVelocity);
					identity(angularVelocity);
				}

				if (def.canSleep)
				{
					type_flags |= brBody::CanSleep;
				}

				if (def.isAwake)
				{
					type_flags |= brBody::IsAwake;
				}
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

			const mat4t GetTransform() const
			{
				return transformMatrix;
			}

			const vec3 GetPosition() const
			{
				return worldpos;
			}
			
			const quat GetOrientation() const
			{
				return orientation;
			}

			void Integrate()
			{
				
			}

			~brBody()
			{
			}

		};

} }
#endif