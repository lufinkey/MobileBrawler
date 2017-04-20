
#include "StageInfo.h"

#pragma once

namespace BrawlerLibrary
{
	class StageLoader
	{
	private:
		fgl::ArrayList<fgl::String> paths;
		fgl::ArrayList<StageInfo> stages;
		
		fgl::AssetManager* assetManager;

	public:
		explicit StageLoader(fgl::Window& window);
		StageLoader();
		
		fgl::AssetManager* getAssetManager() const;
		
		void addPath(const fgl::String&path);
		
		void loadIcons(const fgl::Image&compositeMask=fgl::Image());
		void loadPreviews(const fgl::Image&compositeMask=fgl::Image());
		
		void reloadAssets(const fgl::Image&iconMask=fgl::Image(), const fgl::Image&previewMask=fgl::Image());
		
		const fgl::ArrayList<fgl::String>& getPaths() const;
		const fgl::ArrayList<StageInfo>& getStages() const;
		fgl::ArrayList<StageInfo>& getStages();
	};
}
