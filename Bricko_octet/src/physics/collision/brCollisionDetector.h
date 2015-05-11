namespace octet {
	namespace brickophysics {


	#define CHECK_OVERLAP(axis, index) \
		if (!tryAxis(one, two, (axis), toCentre, (index), pen, best))

		class brCollisionDetector
		{
		public:
			static unsigned generateBoxes(const brCollisionBox& a, const brCollisionBox& b, brCollisionData* data)
			{
				vec3 centre = a.get_axis(3) - b.get_axis(3);

				float penetration = 150000;
				unsigned best = 0xffffff;

			};

		};
	}
}

