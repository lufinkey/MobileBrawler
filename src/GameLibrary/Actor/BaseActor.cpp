
#include "BaseActor.h"

namespace GameLibrary
{
	BaseActor::BaseActor()
	{
		actorType = ACTORTYPE_BASE;
	}

	BaseActor::~BaseActor()
	{
		//
	}

	BaseActor::ActorType BaseActor::getActorType() const
	{
		return actorType;
	}
}