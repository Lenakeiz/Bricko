namespace octet {
	namespace brickophysics {

		class brCollisionBox
		{

		public:

			aabb shape;

			brCollisionBox()
			{
			}

			brCollisionBox(aabb_in s)
			{
				shape = s;
			}

			~brCollisionBox()
			{
			}
		};
	}
}

