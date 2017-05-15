
#include "MenuLoad.hpp"

namespace SmashBros
{
	MenuLoad::MenuLoad(MenuAssetManager* assetManager)
		: assetManager(assetManager),
		loadListener(nullptr),
		characterselect_iconmask(nullptr),
		stageselect_iconmask(nullptr),
		stageselect_previewmask(nullptr)
	{
		//
	}
	
	void MenuLoad::setLoadListener(fgl::BatchLoaderEventListener*listener)
	{
		loadListener = listener;
	}
	
	MenuAssetManager* MenuLoad::getAssetManager() const
	{
		return assetManager;
	}
	
	const fgl::Dictionary& MenuLoad::getMenuBarProperties() const
	{
		return properties_menuBar;
	}
	
	const fgl::Dictionary& MenuLoad::getRulesBarProperties() const
	{
		return properties_rulesBar;
	}
	
	const fgl::Dictionary& MenuLoad::getCharacterSelectPanelProperties() const
	{
		return properties_charselectPanel;
	}
	
	fgl::Image* MenuLoad::getCharacterSelectIconMask() const
	{
		return characterselect_iconmask;
	}
	
	fgl::Image* MenuLoad::getStageSelectIconMask() const
	{
		return stageselect_iconmask;
	}
	
	fgl::Image* MenuLoad::getStageSelectPreviewMask() const
	{
		return stageselect_previewmask;
	}
	
	void MenuLoad::load()
	{
		loadIconMasks();
		loadProperties();
		loadAssets();
	}
	
	void MenuLoad::loadIconMasks()
	{
		//load character select icon mask
		assetManager->loadImage("characterselect/icon_mask.png");
		characterselect_iconmask = assetManager->getImage("characterselect/icon_mask.png");
		
		//load stage select icon mask
		assetManager->loadImage("stageselect/icon_mask.png");
		stageselect_iconmask = assetManager->getImage("stageselect/icon_mask.png");
		
		//load stage select preview mask
		assetManager->loadImage("stageselect/preview_mask.png");
		stageselect_previewmask = assetManager->getImage("stageselect/preview_mask.png");
	}
	
	void MenuLoad::loadProperties()
	{
		//load menu bar properties
		FILE* menuBarFile = assetManager->openFile("elements/menu_bar.plist", "rb");
		if(menuBarFile!=nullptr)
		{
			fgl::Plist::loadFromFile(&properties_menuBar, menuBarFile);
			fgl::FileTools::closeFile(menuBarFile);
		}
		
		//load rules bar properties
		FILE* rulesBarFile = assetManager->openFile("elements/rules_bar.plist", "rb");
		if(rulesBarFile!=nullptr)
		{
			fgl::Plist::loadFromFile(&properties_rulesBar, rulesBarFile);
			fgl::FileTools::closeFile(rulesBarFile);
		}
		
		//load character select panel properties
		FILE* charSelectPanelFile = assetManager->openFile("characterselect/panel.plist", "rb");
		if(charSelectPanelFile!=nullptr)
		{
			fgl::Plist::loadFromFile(&properties_charselectPanel, charSelectPanelFile);
			fgl::FileTools::closeFile(charSelectPanelFile);
		}
	}
	
	void MenuLoad::loadAssets()
	{
		fgl::BatchLoader* batchLoader = new fgl::BatchLoader(assetManager);
		if(loadListener!=nullptr)
		{
			batchLoader->addEventListener(loadListener);
		}
		
		//LOAD MENU ASSETS HERE:
		//TODO: Assets need to be loaded in a non-linear fashion. Maybe an array of strings containing
		//		all of the asset paths could be loaded so that they could be called when needed (ie. @
		//		application launch or upon error. Right now, when an asset isn't loaded and is needed,
		//		the application will crash / break upon calling. This seems very inefficient...

		batchLoader->addTexture("backgrounds/loading.png");
		batchLoader->addTexture("backgrounds/error.png");
		batchLoader->addTexture("backgrounds/main.png");
		
		batchLoader->addTexture("buttons/back.png");
		batchLoader->addTexture("buttons/main/group.png");
		batchLoader->addTexture("buttons/main/solo.png");
		batchLoader->addTexture("buttons/group/rules.png");
		batchLoader->addTexture("buttons/group/smash.png");
		batchLoader->addTexture("buttons/solo/training.png");
		
		batchLoader->addTexture("characterselect/chip_cpu.png");
		batchLoader->addTexture("characterselect/chip_p1.png");
		batchLoader->addTexture("characterselect/chip_p2.png");
		batchLoader->addTexture("characterselect/chip_p3.png");
		batchLoader->addTexture("characterselect/chip_p4.png");
		batchLoader->addTexture("characterselect/icon_frame.png");
		batchLoader->addTexture("characterselect/panel_background_p1.png");
		batchLoader->addTexture("characterselect/panel_background_p2.png");
		batchLoader->addTexture("characterselect/panel_background_p3.png");
		batchLoader->addTexture("characterselect/panel_background_p4.png");
		batchLoader->addTexture("characterselect/panel_background_cpu.png");
		batchLoader->addTexture("characterselect/panel_background_na.png");
		batchLoader->addTexture("characterselect/panel_background_blank.png");
		batchLoader->addTexture("characterselect/panel_overlay_p1.png");
		batchLoader->addTexture("characterselect/panel_overlay_p2.png");
		batchLoader->addTexture("characterselect/panel_overlay_p3.png");
		batchLoader->addTexture("characterselect/panel_overlay_p4.png");
		batchLoader->addTexture("characterselect/panel_overlay_cpu.png");
		batchLoader->addTexture("characterselect/panel_overlay_na.png");
		batchLoader->addTexture("characterselect/panel_overlay_blank.png");
		batchLoader->addTexture("characterselect/readytofight_banner.png");
		
		batchLoader->addTexture("elements/button_arrow_down.png");
		batchLoader->addTexture("elements/button_arrow_left.png");
		batchLoader->addTexture("elements/button_arrow_right.png");
		batchLoader->addTexture("elements/button_arrow_up.png");
		batchLoader->addTexture("elements/headerbar_full.png");
		batchLoader->addTexture("elements/headerbar_small.png");
		batchLoader->addTexture("elements/menu_bar.png");
		batchLoader->addTexture("elements/rules_bar.png");
		
		batchLoader->addFont("fonts/default.ttf");
		//batchLoader->addFont("fonts/"BorisBlackBloxx.ttf");
		
		batchLoader->addTexture("stageselect/icon_frame.png");
		
		batchLoader->addTexture("titlescreen/logo.png");
		batchLoader->addTexture("titlescreen/background.png");
		
		batchLoader->loadAll();
		
		delete batchLoader;
	}
	
	void MenuLoad::unload()
	{
		assetManager->unload();
		properties_menuBar.clear();
		properties_rulesBar.clear();
		properties_charselectPanel.clear();
		
		characterselect_iconmask = nullptr;
		stageselect_iconmask = nullptr;
		stageselect_previewmask = nullptr;
	}
}
