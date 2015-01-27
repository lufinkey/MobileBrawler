
#include "StageInfo.h"

#pragma once

namespace BrawlerLibrary
{
	using namespace GameLibrary;
	
	class StageLoader
	{
	private:
		ArrayList<String> paths;
		ArrayList<StageInfo> stages;
		
		AssetManager* assetManager;

	public:
		StageLoader(Window& window);
		StageLoader();
		
		AssetManager* getAssetManager() const;
		
		void addPath(const String&path);
		
		void loadIcons(const Image&compositeMask=Image());
        void loadAssets(const Image&compositeMask=Image());
		
		const ArrayList<String>& getPaths() const;
		const ArrayList<StageInfo>& getStages() const;
		ArrayList<StageInfo>& getStages();
	};
}
