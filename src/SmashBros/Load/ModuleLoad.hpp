
#pragma once

#include <GameLibrary/GameLibrary.hpp>
#include <SmashLib/SmashLib.hpp>

namespace SmashBros
{
	using namespace fgl;
	using namespace SmashLib;
	
	class ModuleLoad
	{
	private:
		CharacterLoader* characterLoader;
		StageLoader* stageLoader;
		
		const Image* characterselect_iconmask;
		const Image* stageselect_iconmask;
		const Image* stageselect_previewmask;
		
	public:
		ModuleLoad(Window* window, const String&charactersRoot, const String&stagesRoot);
		~ModuleLoad();
		
		void addCharactersPath(const String&);
		void addStagesPath(const String&);
		
		void setCharacterSelectIconMask(const Image* mask);
		void setStageSelectIconMask(const Image* mask);
		void setStageSelectPreviewMask(const Image* mask);
		
		CharacterLoader* getCharacterLoader() const;
		StageLoader* getStageLoader() const;
		
		void load();
		void reload();
		void unload();
	};
}
