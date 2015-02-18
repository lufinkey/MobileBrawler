
#include "InitialLoadListener.h"

namespace SmashBros
{
	InitialLoadListener::InitialLoadListener(Window*win)
	{
		window = win;
	}
	
	void InitialLoadListener::onBatchLoaderStart(BatchLoader*batchLoader)
	{
		GameLibrary::Console::writeLine("Batch loader is starting.");
	}
	
	void InitialLoadListener::onBatchLoaderLoadTexture(BatchLoader*batchLoader, const String&path, unsigned int value)
	{
		GameLibrary::Console::writeLine("Batch loader loaded a texture.");
		AssetManager* assetManager = batchLoader->getAssetManager();
		loadingImage = assetManager->getTexture("backgrounds/loading.png");
		
		Vector2f loadingImageSize(600,900);
		Graphics* graphics = window->getGraphics();
		graphics->drawImage(loadingImage, 0, 0);
		window->refresh();
	}
	
	void InitialLoadListener::onBatchLoaderLoadFont(BatchLoader*batchLoader, const String&path, unsigned int value)
	{
		GameLibrary::Console::writeLine("Batch loader loaded a font.");
	}
	
	void InitialLoadListener::onBatchLoaderErrorTexture(BatchLoader*batchLoader, const String&path, unsigned int value, const String&error)
	{
		GameLibrary::Console::writeLine("Batch loader encountered an error while loading textures!");
		GameLibrary::Console::writeError("Error details:"+path+"\n"+value+"\n"+error);
	}
	
	void InitialLoadListener::onBatchLoaderErrorFont(BatchLoader*batchLoader, const String&path, unsigned int value, const String&error)
	{
		GameLibrary::Console::writeLine("Batch loader encountered an error while loading fonts!");
		GameLibrary::Console::writeError("Error details:"+path+"\n"+value+"\n"+error);
	}
	
	void InitialLoadListener::onBatchLoaderFinish(BatchLoader*batchLoader)
	{
		GameLibrary::Console::writeLine("Batch loader has finished.");
	}
}
