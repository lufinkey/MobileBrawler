
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
		draw(batchLoader, *window->getGraphics());
	}
	
	void InitialLoadListener::onBatchLoaderLoadFont(BatchLoader*batchLoader, const String&path, unsigned int value)
	{
		draw(batchLoader, *window->getGraphics());
	}
	
	void InitialLoadListener::onBatchLoaderErrorTexture(BatchLoader*batchLoader, const String&path, unsigned int value, const String&error)
	{
		draw(batchLoader, *window->getGraphics());
	}
	
	void InitialLoadListener::onBatchLoaderErrorFont(BatchLoader*batchLoader, const String&path, unsigned int value, const String&error)
	{
		draw(batchLoader, *window->getGraphics());
	}
	
	void InitialLoadListener::onBatchLoaderFinish(BatchLoader*batchLoader)
	{
		//
	}

	void InitialLoadListener::draw(BatchLoader*batchLoader, Graphics graphics) const
	{
		TextureImage*loadingImage = batchLoader->getAssetManager()->getTexture("backgrounds/loading.png");
		
		Vector2d viewSize = window->getView()->getSize();
		graphics.drawImage(loadingImage, 0, 0, viewSize.x, viewSize.y);
		window->refresh();
	}
}
