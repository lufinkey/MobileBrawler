
#pragma once

#include <GameLibrary/GameLibrary.h>
#include "SmashData.h"

namespace SmashBros
{
	using namespace GameLibrary;
	
	class InitialLoadListener : public BatchLoaderEventListener
	{
	private:
		Window* window;
	public:
		InitialLoadListener(Window*window);
		TextureImage* loadingImage;
		virtual void onBatchLoaderStart(BatchLoader*batchLoader);
		virtual void onBatchLoaderLoadTexture(BatchLoader*batchLoader, const String&path, unsigned int value);
		//virtual void onBatchLoaderLoadStage(BatchLoader*batchLoader, const String&path, unsigned int value);
		virtual void onBatchLoaderLoadFont(BatchLoader*batchLoader, const String&path, unsigned int value);
		virtual void onBatchLoaderErrorTexture(BatchLoader*batchLoader, const String&path, unsigned int value, const String&error);
		virtual void onBatchLoaderErrorFont(BatchLoader*batchLoader, const String&path, unsigned int value, const String&error);
		//virtual void onBatchLoaderErrorStage(BatchLoader*batchLoader, const String&path, unsigned int value, const String&error);
		virtual void onBatchLoaderFinish(BatchLoader*batchLoader);
	};
}
