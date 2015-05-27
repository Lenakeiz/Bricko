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
		brBroadPhase* broadPhase;
		//ContactGenerator
		brCollisionDetector* collisionDetector;

		std::vector<brBody*> bodies;

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
			broadPhase = new brBroadPhase();
			collisionDetector = new brCollisionDetector();
			//setting gravity
			gravityForce = new Gravity(gravity);
		}

		///This function will run the physics 
		void Run(float dt) //this will be the time step, expected is 1.0/60.0
		{
			//TestCollisions
			//This have to become generate pairs of objects collinding
			TestCollisions();

			//Get out from the broadphase the pairs of pairs of colliding bodies

			//Should add iteration as a parameter
			const int numIterations = 1;
			for (int i = 0; i < numIterations; i++)
			{
				brCollisionData* collision_data = new brCollisionData();
				//Foreach pair of coliiding bodies
					//collisionDetector->generateBoxesData(..etc..);

				if (collision_data != nullptr && collision_data->contactCount != 0)
				{
					for (uint32_t i = 0; i < collision_data->contactCount; i++)
					{
						//Resolve the contact here
						//brContactResolver::ResolveContact();
					}
				}
			}

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

		void TestCollisions()
		{
			for (unsigned i = 0; i < bodies.size() - 1; i++)
			{
				for (unsigned j = i + 1; j < bodies.size(); j++)
				{
					mat4t a = bodies[i]->GetTransformMat4t();					
					mat4t b = bodies[j]->GetTransformMat4t();

					brCollisionBox* boxa = bodies[i]->boxref->collisionVolume;
					brCollisionBox* boxb = bodies[i]->boxref->collisionVolume;

					if (boxa->shape.intersects_old(boxb->shape, a, b))
					{
						int stop = 1;
						printf("Colliding: %d %d \n", i, j);
					}
				}
			}
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


