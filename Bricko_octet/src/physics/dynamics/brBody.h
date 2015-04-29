//
// This class represent the physics body and will contain its properties such as 
//
// Bricko world body
// a body has an orientation, with first derivatives. Subject to forces, torques and impulses.
//

#ifndef BRBODY_INCLUDED
#define BRBODY_INCLUDED

namespace octet { namespace brickophysics {

	enum BodyType{
		Static,
		Dynamic
	};
		
		class brBody
		{


		private:
			
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

		public:

			brBody()
			{
			}

			~brBody()
			{
			}
		};
} }
#endif