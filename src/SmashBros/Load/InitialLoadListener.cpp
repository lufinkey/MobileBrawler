
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
		AssetManager* assetManager = batchLoader->getAssetManager();
		
		loadingImage = assetManager->getTexture("backgrounds/loading.png");
		Vector2f loadingImageSize(800,450);
		Graphics* graphics = window->getGraphics();
		graphics->drawImage(loadingImage, 0, 0);
		window->refresh();
	}
	/*
	 // Eventually we may want to load stage assets at game launch instead of when a character is selected.
	 // This system could be implimented here but in the meantime, until we wonk on loading stage assets, this
	 // will remain commented out of the code.
	void InitialLoadListener::onBatchLoaderLoadStage(BatchLoader*batchLoader, const String&path, unsigned int value)
	{
		//
	}
	*/
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
	/*
	void InitialLoadListener::onBatchLoaderErrorStage(BatchLoader*batchLoader, const String&path, unsigned int value, const String&error)
	{
		
	}
	*/
	void InitialLoadListener::onBatchLoaderFinish(BatchLoader*batchLoader)
	{
		//
	}
}
