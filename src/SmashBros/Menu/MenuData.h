
#pragma once

#include <GameLibraryImport.hpp>

namespace SmashBros
{
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
