
#include "../Screen/ScreenElement.h"

#pragma once

namespace GameLibrary
{
	class BaseActor : private ScreenElement
	{
		friend class Actor;
	public:
		enum ActorType : byte
		{
			ACTORTYPE_BASE,
			ACTORTYPE_NORMAL,
			ACTORTYPE_WIREFRAME,
			ACTORTYPE_TEXT
		};
		typedef enum ActorType ActorType;

		float x;
		float y;

		BaseActor();
		virtual ~BaseActor();

		ActorType getActorType() const;

	private:
		float width;
		float height;

		ActorType actorType;
	};
}
