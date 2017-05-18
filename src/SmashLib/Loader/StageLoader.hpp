
#include "StageInfo.hpp"

#pragma once

namespace SmashLib
{
	class StageLoader
	{
	private:
		fgl::ArrayList<fgl::String> paths;
		fgl::ArrayList<StageInfo> stages;
		
		fgl::AssetManager* assetManager;

	public:
		explicit StageLoader(fgl::Window* window);
		StageLoader();
		
		fgl::AssetManager* getAssetManager() const;
		
		void addPath(const fgl::String&path);
		
		void loadIcons(const fgl::Image* compositeMask=nullptr);
		void loadPreviews(const fgl::Image* compositeMask=nullptr);
		
		void reloadAssets(const fgl::Image* iconMask=nullptr, const fgl::Image* previewMask=nullptr);
		
		const fgl::ArrayList<fgl::String>& getPaths() const;
		const fgl::ArrayList<StageInfo>& getStages() const;
		fgl::ArrayList<StageInfo>& getStages();
	};
}
