//#ifndef BRFGEN_H
//#define BRFGEN_H

//#include "dynamics\brBody.h"

namespace octet{ namespace brickophysics{

	class brForceGenerator
	{
	public:
		
		///Overload this in implementations of the interface to calculate and update the force applied to the given rigid body.
		virtual void updateForce(brBody* body, float dt) = 0;
	};

	class Gravity : brForceGenerator
	{
	private:
		vec3 gravity;
	public:
		
		Gravity(const vec3& _gravity) : gravity(_gravity)
		{			
		}

		virtual void updateForce(brBody *body, float dt)
		{
			if (!body->HasFiniteMass()) return;

			// Apply the mass-scaled force to the body
			body->ApplyLinearForce( gravity * body->GetMass());
		}

	};

} }

//#endif 