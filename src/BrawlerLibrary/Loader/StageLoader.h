
#include "StageInfo.h"

#pragma once

namespace BrawlerLibrary
{
	class StageLoader
	{
	private:
		GameLibrary::ArrayList<GameLibrary::String> paths;
		GameLibrary::ArrayList<StageInfo> stages;
		
		GameLibrary::AssetManager* assetManager;

	public:
		explicit StageLoader(GameLibrary::Window& window);
		StageLoader();
		
		GameLibrary::AssetManager* getAssetManager() const;
		
		void addPath(const GameLibrary::String&path);
		
		void loadIcons(const GameLibrary::Image&compositeMask=GameLibrary::Image());
		void loadPreviews(const GameLibrary::Image&compositeMask=GameLibrary::Image());
		
		void reloadAssets(const GameLibrary::Image&iconMask=GameLibrary::Image(), const GameLibrary::Image&previewMask=GameLibrary::Image());
		
		const GameLibrary::ArrayList<GameLibrary::String>& getPaths() const;
		const GameLibrary::ArrayList<StageInfo>& getStages() const;
		GameLibrary::ArrayList<StageInfo>& getStages();
	};
}
