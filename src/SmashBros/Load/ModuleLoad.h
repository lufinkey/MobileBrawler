
#pragma once

#include <GameLibrary/GameLibrary.h>
#include <BrawlerLibrary/BrawlerLibrary.h>

namespace SmashBros
{
	using namespace GameLibrary;
	using namespace BrawlerLibrary;
	
	class ModuleLoad
	{
	private:
		CharacterLoader* characterLoader;
		//StageLoader* stageLoader;
		
		Image const* characterselect_iconmask;
		Image const* stageselect_iconmask;
		
	public:
		ModuleLoad(Window&window, const String&charactersRoot, const String&stagesRoot);
		~ModuleLoad();
		
		void addCharactersPath(const String&);
		void addStagesPath(const String&);
		
		void setCharacterSelectIconMask(Image const* mask);
		void setStageSelectIconMask(Image const* mask);
		
		CharacterLoader* getCharacterLoader() const;
		//StageLoader* getStageLoader() const;
		
		void load();
		void reload();
		void unload();
	};
}
