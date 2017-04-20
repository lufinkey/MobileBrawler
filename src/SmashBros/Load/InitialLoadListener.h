
#pragma once

#include <GameLibrary/GameLibrary.hpp>

namespace SmashBros
{
	using namespace fgl;
	
	class InitialLoadListener : public BatchLoaderEventListener
	{
	public:
		explicit InitialLoadListener(Window*window);
		virtual void onBatchLoaderStart(BatchLoader*batchLoader);
		virtual void onBatchLoaderLoadTexture(BatchLoader*batchLoader, const String&path, unsigned int value);
		virtual void onBatchLoaderLoadFont(BatchLoader*batchLoader, const String&path, unsigned int value);
		virtual void onBatchLoaderErrorTexture(BatchLoader*batchLoader, const String&path, unsigned int value, const String&error);
		virtual void onBatchLoaderErrorFont(BatchLoader*batchLoader, const String&path, unsigned int value, const String&error);
		virtual void onBatchLoaderFinish(BatchLoader*batchLoader);
	};
}
