namespace octet {
	namespace brickophysics {

		struct brCollisionData
		{

			///Holding a contact array
			brContact* contacts;

			unsigned int contactsLeft;

			brCollisionData()
			{
			}

			~brCollisionData()
			{
			}
		};
	}
}

