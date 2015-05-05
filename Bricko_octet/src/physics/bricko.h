#ifndef OCTET_BRICKO_INCLUDED
#define OCTET_BRICKO_INCLUDED

namespace octet {
	namespace  brickophysics{
		OCTET_HUNGARIANS(brBox);
		OCTET_HUNGARIANS(brBody);
		OCTET_HUNGARIANS(brBroadPhase);
		OCTET_HUNGARIANS(brForceGenerator);
		OCTET_HUNGARIANS(Gravity);
		OCTET_HUNGARIANS(brWorld);
	}
	using namespace brickophysics;
}

#include "shape\brBox.h"
#include "dynamics\brBody.h"
#include "broadphase\brBroadPhase.h"
#include "brForceGenerator.h"
#include "bworld.h"

#endif

