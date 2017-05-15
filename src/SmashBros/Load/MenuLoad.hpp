
#pragma once

#include "MenuAssetManager.hpp"

namespace SmashBros
{
	class MenuLoad
	{
	public:
		MenuLoad(MenuAssetManager* assetManager);
		
		void setLoadListener(fgl::BatchLoaderEventListener*listener);
		
		MenuAssetManager* getAssetManager() const;
		const fgl::Dictionary& getMenuBarProperties() const;
		const fgl::Dictionary& getRulesBarProperties() const;
		const fgl::Dictionary& getCharacterSelectPanelProperties() const;
		
		fgl::Image* getCharacterSelectIconMask() const;
		fgl::Image* getStageSelectIconMask() const;
		fgl::Image* getStageSelectPreviewMask() const;
		
		void load();
		void unload();

	private:
		MenuAssetManager* assetManager;
		fgl::BatchLoaderEventListener* loadListener;

		fgl::Dictionary properties_menuBar;
		fgl::Dictionary properties_rulesBar;
		fgl::Dictionary properties_charselectPanel;

		fgl::Image* characterselect_iconmask;
		fgl::Image* stageselect_iconmask;
		fgl::Image* stageselect_previewmask;

		void loadIconMasks();
		void loadProperties();
		void loadAssets();
	};
}
