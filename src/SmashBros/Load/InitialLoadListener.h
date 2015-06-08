
#pragma once

#include <GameLibrary/GameLibrary.h>

namespace SmashBros
{
	using namespace GameLibrary;
	
	class InitialLoadListener : public BatchLoaderEventListener
	{
	private:
		Window* window;
		
	public:
		explicit InitialLoadListener(Window*window);
		virtual void onBatchLoaderStart(BatchLoader*batchLoader);
		virtual void onBatchLoaderLoadTexture(BatchLoader*batchLoader, const String&path, unsigned int value);
		virtual void onBatchLoaderLoadFont(BatchLoader*batchLoader, const String&path, unsigned int value);
		virtual void onBatchLoaderErrorTexture(BatchLoader*batchLoader, const String&path, unsigned int value, const String&error);
		virtual void onBatchLoaderErrorFont(BatchLoader*batchLoader, const String&path, unsigned int value, const String&error);
		virtual void onBatchLoaderFinish(BatchLoader*batchLoader);

		virtual void draw(BatchLoader*batchLoader, Graphics graphics, String image) const;
	};
}
