
#pragma once

#include <GameLibrary/GameLibrary.h>

namespace SmashBros
{
	using namespace GameLibrary;
	
	namespace Menu
	{
		class MenuData
		{
		private:
			AssetManager* assetManager;
			
		public:
			MenuData(AssetManager*assetManager);
			
			AssetManager* getAssetManager() const;
		};
	}
}
