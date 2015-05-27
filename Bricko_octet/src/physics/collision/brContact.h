namespace octet {
	namespace brickophysics {
		
		class brContact
		{
		public:

			uint32_t contactsCount;
			///holding bodies that are involved in contacts
			brBody* bodies[2];

			float friction;

			float restitution;

			///world coordinates of contact point
			vec3 contactPoint;

			///world coordinates of direction of the contact
			vec3 contactNormal;

			///the depth is the midway between inter-prenetating points
			float penetration;

			//This function will help connecting the contact to its relative bodies
			void setData(brBody* a, brBody* b, float _friction, float _restitution)
			{
				bodies[0] = a;
				bodies[1] = b;
				friction = _friction;
				restitution = _restitution;
			}

			brContact()
			{
			}

			~brContact()
			{
			}

		protected:

		private:


		};

	}
}