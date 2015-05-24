namespace octet {
	namespace brickophysics {

		struct brCollisionData
		{

			///This will be a fixed to the first contact so we can loop by incrementing the array
			brContact* contactStart;

			///Holding a contact array
			brContact* contacts;

			///This will hold the maximum number of contacts handled by the engine
			unsigned int contactsLeft;
			unsigned int contactCount;
			//TODO friction will be implemented later one, for now just elastic collisions
			float friction;

			//Ratio  of speed after the collision is exploited
			float restitution;

			void addContacts(unsigned count)
			{
				contactsLeft -= count;
				contactCount += count;

				//Moving the array
				contacts += count;
			}

			brCollisionData()
			{
			}

			~brCollisionData()
			{
			}

		};
	}
}

