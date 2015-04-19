
#pragma once

#include "Platform.h"
#include "../../Loader/StageInfo.h"

namespace BrawlerLibrary
{
	class BrawlGame;
	
	class Stage : GameLibrary::Updateable
	{
	public:
		Stage(BrawlGame*gameInstance, const StageInfo&info);
		virtual ~Stage();
		
		virtual void update(GameLibrary::ApplicationData appData) override;
	};
}
