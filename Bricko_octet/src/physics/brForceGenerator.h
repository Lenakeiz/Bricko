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

	class Gravity : public brForceGenerator
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

	///Millington
	class ForceRegistry
	{

	protected:

		struct ForceRegistration
		{
			brBody* body;
			brForceGenerator* fg;
		};

		dynarray<ForceRegistration> registrations;
	public:

		void add(brBody *body, brForceGenerator *fg)
		{
			ForceRegistry::ForceRegistration registration;
			registration.body = body;
			registration.fg = fg;
			registrations.push_back(registration);
		}

		void updateForces(float dt)
		{
			for (unsigned int i = 0; i < registrations.size(); i++)
			{
				registrations[i].fg->updateForce(registrations[i].body, dt);
			}
		}

	};

} }

//#endif 