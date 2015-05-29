namespace octet {
	namespace brickophysics {

		struct brCollisionData
		{

			///Holding a contact array
			std::vector<brContact*> contacts;

			///This will hold the maximum number of contacts handled by the engine
			uint32_t contactsLeft;

			//TODO friction will be implemented later one, for now just elastic collisions
			float friction;

			//Ratio  of speed after the collision is exploited
			float restitution;

			void SetFriction(float t)
			{
				friction = t;
			}

			void SetRestitution(float r)
			{
				restitution = r;
			}

			void SetMaximumContacts(uint32_t _n)
			{
				contactsLeft = _n;
			}

			void Init()
			{
				contacts.reserve(contactsLeft);
			}

			bool addContact(unsigned count, brContact* contact)
			{
				contacts.push_back(contact);
				contactsLeft -= 1;
				return contactsLeft == 0;
			}

			brCollisionData()
			{
				//This is a default value
				contactsLeft = 100;
			}

			~brCollisionData()
			{
			}

		};
	}
}

