
#pragma once

#include <SmashBros/Module/ModuleManager.hpp>

namespace SmashBros
{
	namespace Menu
	{
		class MenuData
		{
		public:
			MenuData(fgl::AssetManager* assetManager, const ModuleManager* moduleManager);

			fgl::AssetManager* getAssetManager() const;
			const ModuleManager* getModuleManager() const;

			fgl::Dictionary info;

		private:
			fgl::AssetManager* assetManager;
			const ModuleManager* moduleManager;
		};
	}
}
