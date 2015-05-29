//
// This class detect collisions
// It is not properly a broad phase collision detector since it does not use a proper hierarchy tree
// It use a fast detection by costructing the Minkowski difference of the two cubes.
// 
//

namespace octet {
	namespace brickophysics {

		struct BodyPair
		{
			brBody* bodies[2];
			BodyPair(brBody* b1, brBody* b2)
			{
				bodies[0] = b1;
				bodies[1] = b2;
			}

		};

		class brBroadPhase
		{
			
		private:

			std::vector<BodyPair> pairs;

		public:

			void generatePairs(const std::vector<brBody*>& bodiesList)
			{
				if (pairs.size() != 0)
				{
					pairs.clear();
				}

				for (uint32_t i = 0; i < bodiesList.size() - 1; i++)
				{
					for (uint32_t j = i + 1; j < bodiesList.size(); j++)
					{
						mat4t a = bodiesList[i]->GetTransformMat4t();
						mat4t b = bodiesList[j]->GetTransformMat4t();

						brCollisionBox* boxa = bodiesList[i]->boxref->collisionVolume;
						brCollisionBox* boxb = bodiesList[j]->boxref->collisionVolume;

						if (boxa->shape.intersects_old(boxb->shape, a, b))
						{
							#ifdef DEBUG
							printf("Colliding shape : %f %f \n", a, b);
							#endif
							pairs.push_back(BodyPair(bodiesList[i], bodiesList[j]));
						}
					}
				}
			}

			const std::vector<BodyPair>& GetPairs()
			{
				return pairs;
			}

			brBroadPhase()
			{

			}

			~brBroadPhase()
			{

			}
		};
	}
}


