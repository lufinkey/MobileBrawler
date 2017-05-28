
#pragma once

#include <fightlib/fightlib.hpp>
#include "StageInfo.hpp"

namespace SmashBros
{
	class StageLoader
	{
	public:
		StageLoader();
		
		void addPath(const fgl::String& path);
		void reloadPaths();
		
		const fgl::ArrayList<fgl::String>& getPaths() const;
		const fgl::ArrayList<StageInfo>& getStages() const;
		bool hasStage(const fgl::String& identifier) const;
		const StageInfo& getStageInfo(const fgl::String& identifier) const;

		fgl::ArrayList<fgl::String> getIconPaths() const;
		fgl::ArrayList<fgl::String> getPreviewPaths() const;

		void registerStage(const fgl::String& identifier, const std::function<fl::Stage*()>& initializer);
		void unregisterStage(const fgl::String& identifier);
		fl::Stage* createStage(const fgl::String& identifier) const;

	private:
		fgl::ArrayList<StageInfo> stages;
		fgl::ArrayList<fgl::String> paths;

		fgl::BasicDictionary<fgl::String, std::function<fl::Stage*()>> stageInitializers;
	};
}
