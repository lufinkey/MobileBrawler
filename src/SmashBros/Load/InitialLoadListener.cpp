
#include "InitialLoadListener.h"

namespace SmashBros
{
	InitialLoadListener::InitialLoadListener(Window*win)
	{
		window = win;
	}
	
	void InitialLoadListener::onBatchLoaderStart(BatchLoader*batchLoader)
	{
		//Called so that the loader has time to load the error.png incase of emergency
		//Otherwise, this wouldn't be needed and would be replaced with "//"
		draw(batchLoader, *window->getGraphics(), "backgrounds/loading.png");
	}
	
	void InitialLoadListener::onBatchLoaderLoadTexture(BatchLoader*batchLoader, const String&path, unsigned int value)
	{
		draw(batchLoader, *window->getGraphics(), "backgrounds/loading.png");
	}
	
	void InitialLoadListener::onBatchLoaderLoadFont(BatchLoader*batchLoader, const String&path, unsigned int value)
	{
		draw(batchLoader, *window->getGraphics(), "backgrounds/loading.png");
	}
	
	void InitialLoadListener::onBatchLoaderErrorTexture(BatchLoader*batchLoader, const String&path, unsigned int value, const String&error)
	{
		//TODO: Is there a way to keep the app from exiting upon crash so that it has time to display the error screen?
		draw(batchLoader, *window->getGraphics(), "backgrounds/error.png");
		Console::writeErrorLine("Texture Error: " + error);
	}
	
	void InitialLoadListener::onBatchLoaderErrorFont(BatchLoader*batchLoader, const String&path, unsigned int value, const String&error)
	{
		//TODO: Is there a way to keep the app from exiting upon crash so that it has time to display the error screen?
		draw(batchLoader, *window->getGraphics(), "backgrounds/error.png");
		Console::writeErrorLine("Texture Error: " + error);
	}
	
	void InitialLoadListener::onBatchLoaderFinish(BatchLoader*batchLoader)
	{
		//
	}

	void InitialLoadListener::draw(BatchLoader*batchLoader, Graphics graphics, String image) const
	{
		TextureImage*loadingImage = batchLoader->getAssetManager()->getTexture(image);
		
		Vector2d viewSize = window->getView()->getSize();
		graphics.drawImage(loadingImage, 0, 0, viewSize.x, viewSize.y);
		window->refresh();
	}
}
