
#include "MenuData.h"

namespace SmashBros
{
	namespace Menu
	{
		MenuData::MenuData(AssetManager*assetMgr)
		{
			assetManager = assetMgr;
		}
		
		AssetManager* MenuData::getAssetManager() const
		{
			return assetManager;
		}
	}
}
