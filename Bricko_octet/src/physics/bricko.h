#ifndef OCTET_BRICKO_INCLUDED
#define OCTET_BRICKO_INCLUDED

namespace octet {
	namespace  brickophysics{
		OCTET_HUNGARIANS(brBox);
		OCTET_HUNGARIANS(brBody);
		OCTET_HUNGARIANS(brCollisionBox);
		OCTET_HUNGARIANS(brBroadPhase);
		OCTET_HUNGARIANS(brForceGenerator);
		OCTET_HUNGARIANS(Gravity);
		OCTET_HUNGARIANS(ForceRegistry);
		OCTET_HUNGARIANS(brContact);
		OCTET_HUNGARIANS(brCollisionDetector);
		OCTET_HUNGARIANS(brContactResolver);
		OCTET_HUNGARIANS(brWorld);
	}
	using namespace brickophysics;
}

#include "shape\brBox.h"
#include "shape\brCollisionBox.h"
#include "dynamics\brBody.h"
#include "broadphase\brBroadPhase.h"
#include "brForceGenerator.h"
#include "collision\brContact.h"
#include "collision\brCollisionData.h"
#include "collision\brCollisionDetector.h"
#include "collision\brContactResolver.h"
#include "bworld.h"

#endif

