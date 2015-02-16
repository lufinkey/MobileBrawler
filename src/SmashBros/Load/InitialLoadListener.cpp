
#include "InitialLoadListener.h"

namespace SmashBros
{
	InitialLoadListener::InitialLoadListener(Window*win)
	{
		window = win;
	}
	
	void InitialLoadListener::onBatchLoaderStart(BatchLoader*batchLoader)
	{
		//
	}
	
	void InitialLoadListener::onBatchLoaderLoadTexture(BatchLoader*batchLoader, const String&path, unsigned int value)
	{
		ImageElement* logo;
		SmashData* SmashData = nullptr;
		AssetManager* assetManager = SmashData->getMenuData()->getAssetManager();
		
		TextureImage* loadingImage = assetManager->getTexture("backgrouns/loading.png");
		Vector2f loadingImageSize(0,0);
		if(loadingImage != nullptr)
		{
			loadingImageSize.x = (float)loadingImage->getWidth();
			loadingImageSize.y = (float)loadingImage->getHeight();
		}
		logo = new ImageElement(loadingImage, ImageElement::DISPLAY_FIT);
		
		window->getGraphics()->drawImage(loadingImage, 0, 0);
		window->refresh();
	}
	
	void InitialLoadListener::onBatchLoaderLoadFont(BatchLoader*batchLoader, const String&path, unsigned int value)
	{
		//
	}
	
	void InitialLoadListener::onBatchLoaderErrorTexture(BatchLoader*batchLoader, const String&path, unsigned int value, const String&error)
	{
		//
	}
	
	void InitialLoadListener::onBatchLoaderErrorFont(BatchLoader*batchLoader, const String&path, unsigned int value, const String&error)
	{
		//
	}
	
	void InitialLoadListener::onBatchLoaderFinish(BatchLoader*batchLoader)
	{
		//
	}
}
