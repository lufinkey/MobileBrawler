
#pragma once

#include <GameLibrary/GameLibrary.h>

namespace SmashBros
{
	using namespace GameLibrary;
	
	class MenuLoad
	{
	private:
		String primaryDirectory;
		String secondaryDirectory;

		AssetManager* assetManager;
		BatchLoaderEventListener* loadListener;
		
		Dictionary properties_menuBar;
		Dictionary properties_rulesBar;
		Dictionary properties_charselectPanel;
		
		Image characterselect_iconmask;
		Image stageselect_iconmask;
		
		void loadIconMasks();
		void loadProperties();
		void loadAssets();
		
	public:
		MenuLoad(Window&window, const String& primaryDirectory);
		MenuLoad(Window&window, const String& primaryDirectory, const String&secondaryDirectory);
		~MenuLoad();
		
		void setLoadListener(BatchLoaderEventListener*listener);
		
		AssetManager* getAssetManager() const;
		const Dictionary& getMenuBarProperties() const;
		const Dictionary& getRulesBarProperties() const;
		const Dictionary& getCharacterSelectPanelProperties() const;
		
		const Image& getCharacterSelectIconMask() const;
		const Image& getStageSelectIconMask() const;
		
		void load();
		void reload();
		void unload();
	};
}
