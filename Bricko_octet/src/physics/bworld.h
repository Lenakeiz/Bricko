//
// This class represent the physics world and will handle the physics
//
// Bricko world
//

#ifndef BRWORLD_INCLUDED
#define BRWORLD_INCLUDED

#include "dynamics\brBody.h"
#include "shape\brBox.h"

namespace octet { namespace brickophysics {

	class brWorld
	{

	private:
		
		//Broadphase
		//ContactGenerator
		//ContactList
		//ContactResolver

		dynarray<brBody*> bodies;

		void ApplyForces(brBody* bd)
		{
			//to a body can be applied more kind of forces (all derived from force generator)
			
		}

	public:		

		void Init()
		{
			//this function will init all the classes handled by the bWorld
		}

		///This function will run the physics 
		void Run(float dt) ///this will be the time step, expected is 1.0/60.0
		{

			//Move objects
			for each (brBody* body in bodies)
			{
				//integrate velocity
				body->Integrate(dt);
				
				//Apply forces (gravity)
				ApplyForces(body);				
			}

			

		}

		void addBody(const brBodyDef& body_def)
		{
			brBody* body = new brBody(body_def, this);
			bodies.push_back(body);

			//Later on we will add the body to the broadphase manager

		}

		brWorld()
		{
		}

		~brWorld()
		{
		}
	};
} }
#endif


