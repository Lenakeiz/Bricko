namespace octet {
	namespace brickophysics {
		
		class Contact
		{
		public:

			float friction;

			float restitution;

			///world coordinates of contact point
			vec3 contactPoint;

			///world coordinates of direction of the contact
			vec3 contactNormal;

			///the depth is the midway between inter-prenetating points
			float penatration;

			Contact()
			{
			}

			~Contact()
			{
			}
		};

	}
}