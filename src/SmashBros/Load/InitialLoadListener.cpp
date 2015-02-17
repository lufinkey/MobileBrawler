
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
		AssetManager* assetManager = batchLoader->getAssetManager();
		
		TextureImage* loadingImage = assetManager->getTexture("backgrounds/loading.png");
		Vector2f loadingImageSize(800,450);
		logo = new ImageElement(loadingImage, ImageElement::DISPLAY_FIT);
		
		Graphics* graphics = window->getGraphics();
		graphics->drawImage(loadingImage, 0, 0);
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
