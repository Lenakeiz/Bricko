namespace octet {
	namespace brickophysics {

		class brContactResolver
		{
		public:

			static void ResolveVelocities(brContact* contact, uint32_t contactsCount, int iterations)
			{
				
			}

			static void ResolveContact(brContact contact, int iterations)
			{
				//Need to add awake status check
				//ResolveVelocities(contact, iterations);
				//ResolvePositions(contact, iterations);
			}

			brContactResolver()
			{
			}

			~brContactResolver()
			{
			}
		};
	}
}