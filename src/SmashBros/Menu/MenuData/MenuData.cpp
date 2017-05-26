
#include "MenuData.hpp"

namespace SmashBros
{
	namespace Menu
	{
		MenuData::MenuData(fgl::AssetManager* assetManager, const ModuleManager* moduleManager)
			: assetManager(assetManager),
			moduleManager(moduleManager)
		{
			//
		}

		fgl::AssetManager* MenuData::getAssetManager() const
		{
			return assetManager;
		}

		const ModuleManager* MenuData::getModuleManager() const
		{
			return moduleManager;
		}
	}
}
