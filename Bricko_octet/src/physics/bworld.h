//
// This class represent the physics world and will handle the physics
//
// Bricko world
//

//#ifndef BRWORLD_INCLUDED
//#define BRWORLD_INCLUDED

//#include "shape\brBox.h"
//#include "dynamics\brBody.h"
//
//#include "brForceGenerator.h"

namespace octet { namespace brickophysics {

	class brWorld
	{

	private:
		
		//Broadphase
		//ContactGenerator
		//ContactList
		//ContactResolver

		dynarray<brBody*> bodies;
		ForceRegistry forceregistry;

		brForceGenerator* gravityForce;

		void ApplyForces(float dt)
		{
			//to a body can be applied more kind of forces (all derived from force generator)
			forceregistry.updateForces(dt);
		}

	public:		

		void Init(const vec3& gravity)
		{
			//this function will init all the classes handled by the bWorld

			//setting gravity
			gravityForce = new Gravity(gravity);
		}

		///This function will run the physics 
		void Run(float dt) //this will be the time step, expected is 1.0/60.0
		{
			//Apply forces
			ApplyForces(dt);

			for each (brBody* body in bodies)
			{
				//integrate velocity
				body->Integrate(dt);
				body->ClearAccumulators();
			}
		}

		void UpdateRenderingPos()
		{
			for each (brBody* body in bodies)
			{
				//set the scene node by getting the user data
				//octet::scene::scene_node* node = (octet::scene::scene_node*)body->GetUserData();
				//brTransform tr = body->GetTransform();
				//mat4t mat = generate_mat4t(tr.rotation, tr.position);
				//node->access_nodeToParent();// = mat;
			}
		}

		brBody* addBody(const brBodyDef& body_def, const brBoxDef& box_def)
		{
			brBody* body = new brBody(body_def, this);
			body->ConnectBox(box_def);
			bodies.push_back(body);
			forceregistry.add(body, gravityForce);
			//Later on we will add the body to the broadphase manager
			return body;
		}

		brWorld()
		{
		}

		~brWorld()
		{
		}
	};
} }
//#endif


